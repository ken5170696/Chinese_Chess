#pragma once
#include <iostream>
#include <vector>
#include "Chess.h"
#include "GameHeader.h"
class Player {
private:
	Team team;
	std::vector<Chess*> chessList;
	std::vector<Chess*> validMoveChessList;
	sf::String name;
	sf::Font font;
	sf::Event event;
	sf::Text nameText;
	bool out;
public:
	Player();
	Player(Team _team);
	Player(const Player& player);

	void draw(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void setInitChess(Team _team);
	void setChessList(const std::vector<Chess*>& _chessList);
	std::vector<Chess*> getChessList() const;
	void setName(sf::RenderWindow* window);
	sf::String getName() const;
	friend void setChessInitPos(std::vector<Chess*>& chessList, Player& player);
	void handleRealtimeInput(sf::RenderWindow* window);
	
};

//class ChessManager;
//
//#include <iostream>
//#include <vector>
//#include "GameHeader.h"
//#include "ChessManager.h"
//
//class Player
//{
//
//private:
//	Team team;
//	std::vector<Chess*> chessList;
//	std::vector<Chess*> validMoveChessList;
//	Chess* selectPathChess;
//	Chess* selectChess;
//
//public:
//	Player();
//	Player(Team _team);
//	Player(const Player& player);
//
//public:
//	std::vector<Chess*> getChessList() const { return chessList; }
//	void initialPlayer(Team _team);
//	void setValidMoveChessList(std::vector<Chess*>& _validMoveChessList) {
//		validMoveChessList = _validMoveChessList;
//	};
//	void setSelectedPathChess(Chess* _selectPathChess) {
//		selectPathChess = _selectPathChess;
//	}
//	void setSelectChess(Chess* _selectChess) {
//		selectChess = _selectChess;
//	}
//	void handleEvent(const sf::Event& event, ChessManager& commands);
//	void handleRealtimeInput(ChessManager& commands, Status status, Board& board);
//
//	void checkmate(const Player& opponent, const Board& board);
//public:
//	friend void setChessInitPos(std::vector<Chess*>& chessList, Player& player);
//
//};
//
//void setChessInitPos(std::vector<Chess*>& chessList, Player& player);