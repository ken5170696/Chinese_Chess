#pragma once
#include <functional>
#include "Chess.h"
// command interface
class ChessCommand
{
protected:
	Chess* selectedChess;
public:
	virtual std::vector<sf::Vector2f> execute(Chess& selectedChess) = 0;
	Chess* getSelectedChess() { return selectedChess; };
	virtual void undo() = 0;
};

class ChessFindPath : public ChessCommand {
private:
	std::vector<Chess*> chessList;
	const Board* board;
	sf::Vector2i mousePosition;
public:
	ChessFindPath(std::vector<Chess*> _chessList, const Board& _board, sf::Vector2i _mousePosition);
	virtual std::vector<sf::Vector2f> execute(Chess& selectedChess) override;
	virtual void undo() override;
};

class ChessMove : public ChessCommand {
private:
	std::vector<Chess*> tmpChessList;
	Board* board;
	sf::Vector2i mousePosition;

public:
	ChessMove(std::vector<Chess*> _tmpChessList, Board& _board, sf::Vector2i _mousePosition);
	virtual std::vector<sf::Vector2f> execute(Chess& selectedChess) override;
	virtual void undo() override;
};