#include "ChessCommand.h"

ChessFindPath::ChessFindPath(std::vector<Chess*> _chessList, const Board& _board, sf::Vector2i _mousePosition)
{
	chessList = _chessList;
	board = &_board;
	mousePosition = _mousePosition;
}

bool ChessFindPath::validMove(Chess& selectedChess, sf::Vector2f goalPos)
{

	Board tmpBoard = *board;
	bool valid = true;
	sf::Vector2f originalPos = selectedChess.getBoardPosition();
	sf::Vector2f kingPos;

	tmpBoard.setBoard(&selectedChess, goalPos);

	selectedChess.setBoardPosition(goalPos);
	for (auto const& chessY : tmpBoard.getBoard())
	{
		for (auto const& chessX : chessY)
		{
			if (chessX != nullptr && chessX->getTeam() == selectedChess.getTeam())
			{
				if (chessX->getCharacters() == Characters::King)
				{
					kingPos = chessX->getPosition();
				}
			}
		}
	}

	for (int y = 0;y < 10;y++)
	{
		for (int x = 0;x < 9;x++)
		{
			if (tmpBoard.getBoard()[y][x] != nullptr && tmpBoard.getBoard()[y][x]->getTeam() != selectedChess.getTeam())
			{
				std::vector <sf::Vector2f> tmpPath = tmpBoard.getBoard()[y][x]->findPath(tmpBoard);
				for (auto const& path : tmpPath)
				{
					if (path == kingPos)
					{
						selectedChess.setBoardPosition(originalPos);
						return false;
					}

				}
			}
		}
	}
	selectedChess.setBoardPosition(originalPos);
	return true;
}

std::vector<sf::Vector2f> ChessFindPath::execute(Chess& selectedChess)
{
	std::vector<sf::Vector2f> validPath;
	for (auto& chess : chessList) {
		if (validPath.size() != 0)
			break;
		if (chess->isPressed()) {
			validPath = chess->findPath(*board);
			for (int index = 0;index < validPath.size();index++)
			{
				if (!validMove(*chess, validPath[index]))
				{
					validPath.erase(validPath.begin() + index);
					index--;
				}
			}
			this->selectedChess = chess;
		}
	}
	return validPath;
}

void ChessFindPath::undo()
{
}

ChessMove::ChessMove(std::vector<Chess*> _tmpChessList, Board& _board, sf::Vector2i _mousePosition)
{
	tmpChessList = _tmpChessList;
	board = &_board;
	mousePosition = _mousePosition;
}


std::vector<sf::Vector2f> ChessMove::execute(Chess& selectedChess)
{
	std::vector<sf::Vector2f> validPath;
	for (const auto& chess : tmpChessList) {
		if (validPath.size() != 0)
			break;
		if (chess->isPressed()) {
			validPath.push_back(sf::Vector2f());
			selectedChess.move(chess, *board);

		}
	}
	return validPath;
}

void ChessMove::undo()
{
}
