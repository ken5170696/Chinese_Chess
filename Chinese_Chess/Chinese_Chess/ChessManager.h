#pragma once
class ChessCommand;
#include <deque>
#include "ChessCommand.h"
/* �޲z�� Chess �����O*/
class ChessManager
{
private:
	std::deque< ChessCommand* > commandQueue;
	Chess* selectedChess;
public:
	void setCommand(ChessCommand* cmd);
	Chess* getSelectedChess() { return selectedChess; };
	std::vector<sf::Vector2f> doCommand(Chess& selectedChess);
	size_t getCommandNum() const { return commandQueue.size(); };
	/*void setCommand(ChessCommand*); */
};

