#include "ChessManager.h"

void ChessManager::setCommand(ChessCommand* cmd)
{
	commandQueue.push_back(cmd);
}

std::vector<sf::Vector2f> ChessManager::doCommand(Chess& selectedChess)
{
	std::vector<sf::Vector2f> validPath;
	if (commandQueue.size()) {
		validPath = commandQueue.front()->execute(selectedChess);
		this->selectedChess = commandQueue.front()->getSelectedChess();
		commandQueue.pop_front();
	}
	return validPath;
}
