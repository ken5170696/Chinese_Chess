#include "ChessCommand.h"

ChessFindPath::ChessFindPath(std::vector<Chess*> _chessList, const Board& _board, sf::Vector2i _mousePosition)
{
	chessList = _chessList;
	board = &_board;
	mousePosition = _mousePosition;
}

std::vector<sf::Vector2f> ChessFindPath::execute(Chess& selectedChess)
{
	std::vector<sf::Vector2f> validPath;
	for (auto& chess : chessList) {
		if (validPath.size() != 0)
			break;
		if (chess->getIsPressed()) {
			validPath = chess->findPath(*board);
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
		if (chess->getIsPressed()) {
			validPath.push_back(sf::Vector2f());
			selectedChess.move(chess, *board);
		}
	}
	return validPath;
}

void ChessMove::undo()
{
}
