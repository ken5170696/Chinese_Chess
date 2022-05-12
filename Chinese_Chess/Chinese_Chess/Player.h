#pragma once
class ChessManager;

#include <iostream>
#include <vector>
#include "GameHeader.h"
#include "ChessManager.h"

class Player
{

private:
	Team team;
	std::vector<Chess*> chessList;
	std::vector<Chess*> validMoveChessList;
	Chess* selectPathChess;
	Chess* selectChess;

public:
	Player(Team _team);

public:
	std::vector<Chess*> getChessList() const { return chessList; }
	void setValidMoveChessList(std::vector<Chess*>& _validMoveChessList) {
		validMoveChessList = _validMoveChessList;
	};
	void setSelectedPathChess(Chess* _selectPathChess) {
		selectPathChess = _selectPathChess;
	}
	void setSelectChess(Chess* _selectChess) {
		selectChess = _selectChess;
	}
	void handleEvent(const sf::Event& event, ChessManager& commands);
	void handleRealtimeInput(ChessManager& commands, Status status, Board& board);

	void checkmate(const Player& opponent, const Board& board);
public:
	friend void setChessInitPos(std::vector<Chess*>& chessList, Player& player);

};

void setChessInitPos(std::vector<Chess*>& chessList, Player& player);
