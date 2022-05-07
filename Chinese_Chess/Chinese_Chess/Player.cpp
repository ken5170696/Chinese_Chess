#include "Player.h"
/*
  0 1 2 3 4 5 6 7 8
0  _ _ _ _ _ _ _ _
  | | | |\|/| | | |
1  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
2  ─*─ ─ ─ ─ ─ ─*─
  | | | | | | | | |
3 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | |
4  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
  |               |
5  _ _ _ _ _ _ _ _
  | | | | | | | | |
6 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | |
7  ─*─ ─ ─ ─ ─ ─*─ 
  | | | |\|/| | | |
8  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
9  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
*/

Player::Player(Team _team)
{
	team = _team;

	Factory chessFac;
	Chess* tmpChess;
	tmpChess = chessFac.getChess(Characters::King, team);
	chessList.push_back(tmpChess);
	for (int charIdx = int(Characters::Advisors); charIdx <= int(Characters::Cannons); charIdx++) {
		for (int num = 0; num < 2; num++) {
			tmpChess = chessFac.getChess(Characters(charIdx), team);
			chessList.push_back(tmpChess);
		}
	}
	for (int num = 0; num < 5; num++) {
		tmpChess = chessFac.getChess(Characters::Soldiers, team);
		chessList.push_back(tmpChess);
	}
	setChess(chessList, *this);
}

// set chess initial position
void setChess(std::vector<Chess*>& chessList, Player& player) {
	std::cout << chessList.size() << "\n";
	if (player.team == Team::Red) {

		chessList[0]->setPosition(sf::Vector2f(4, 0));

		chessList[1]->setPosition(sf::Vector2f(3, 0));
		chessList[2]->setPosition(sf::Vector2f(5, 0));

		chessList[3]->setPosition(sf::Vector2f(2, 0));
		chessList[4]->setPosition(sf::Vector2f(6, 0));

		chessList[5]->setPosition(sf::Vector2f(0, 0));
		chessList[6]->setPosition(sf::Vector2f(8, 0));

		chessList[7]->setPosition(sf::Vector2f(1, 0));
		chessList[8]->setPosition(sf::Vector2f(7, 0));

		chessList[9]->setPosition(sf::Vector2f(1, 2));
		chessList[10]->setPosition(sf::Vector2f(7, 2));

		chessList[11]->setPosition(sf::Vector2f(0, 3));
		chessList[12]->setPosition(sf::Vector2f(2, 3));
		chessList[13]->setPosition(sf::Vector2f(4, 3));
		chessList[14]->setPosition(sf::Vector2f(6, 3));
		chessList[15]->setPosition(sf::Vector2f(8, 3));
	}
	else if (player.team == Team::Black) {
		
		chessList[0]->setPosition(sf::Vector2f(4, 9));

		chessList[1]->setPosition(sf::Vector2f(3, 9));
		chessList[2]->setPosition(sf::Vector2f(5, 9));

		chessList[3]->setPosition(sf::Vector2f(2, 9));
		chessList[4]->setPosition(sf::Vector2f(6, 9));

		chessList[5]->setPosition(sf::Vector2f(0, 9));
		chessList[6]->setPosition(sf::Vector2f(8, 9));

		chessList[7]->setPosition(sf::Vector2f(1, 9));
		chessList[8]->setPosition(sf::Vector2f(7, 9));

		chessList[9]->setPosition(sf::Vector2f(1, 7));
		chessList[10]->setPosition(sf::Vector2f(7, 7));

		chessList[11]->setPosition(sf::Vector2f(0, 6));
		chessList[12]->setPosition(sf::Vector2f(2, 6));
		chessList[13]->setPosition(sf::Vector2f(4, 6));
		chessList[14]->setPosition(sf::Vector2f(6, 6));
		chessList[15]->setPosition(sf::Vector2f(8, 6));
	}
}
