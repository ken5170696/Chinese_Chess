#pragma once
#include <iostream>
#include <vector>

#include "GameHeader.h"
#include "Chess.h"

class Player
{

private:
	Team team;
	std::vector<Chess*> chessList;

public:
	Player(Team _team);
	friend void setChess(std::vector<Chess*>& chessList, Player& player);
	std::vector<Chess*> getChessList() const { return chessList; }
};

void setChess(std::vector<Chess*>& chessList, Player& player);
