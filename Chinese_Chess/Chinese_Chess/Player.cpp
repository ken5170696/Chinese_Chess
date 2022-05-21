#include "Player.h"

Player::Player()
{
	team = Team::none;
}

Player::Player(Team _team)
{
	setInitChess(_team);
}
Player::Player(const Player& player)
{
	team = player.team;
	chessList = player.chessList;
}
void Player::update(const sf::RenderWindow& window)
{
}
void Player::setInitChess(Team _team)
{
	team = _team;
	Factory chessFac;
	Chess* tmpChess;

	// Initialize chess by team
	int tmpId = 0;
	tmpChess = chessFac.getChess(Characters::King, team, tmpId++);
	chessList.push_back(tmpChess);
	for (int charIdx = int(Characters::Advisors); charIdx <= int(Characters::Cannons); charIdx++) {
		for (int num = 0; num < 2; num++) {
			tmpChess = chessFac.getChess(Characters(charIdx), team, tmpId++);
			chessList.push_back(tmpChess);
		}
	}
	for (int num = 0; num < 5; num++) {
		tmpChess = chessFac.getChess(Characters::Soldiers, team, tmpId++);
		chessList.push_back(tmpChess);
	}
	setChessInitPos(chessList, *this);
}
void Player::setChessList(const std::vector<Chess*>& _chessList)
{
	this->chessList = _chessList;
}
std::vector<Chess*> Player::getChessList() const
{
	return chessList;
}
void Player::setName(const sf::String& _name)
{
	name = _name;
}
sf::String Player::getName() const
{
	return name;
}
void Player::handleRealtimeInput()
{
}
void setChessInitPos(std::vector<Chess*>& chessList, Player& player) {
	if (player.team == Team::Red) {

		chessList[0]->setBoardPosition(sf::Vector2f(4, 0));

		chessList[1]->setBoardPosition(sf::Vector2f(3, 0));
		chessList[2]->setBoardPosition(sf::Vector2f(5, 0));

		chessList[3]->setBoardPosition(sf::Vector2f(2, 0));
		chessList[4]->setBoardPosition(sf::Vector2f(6, 0));

		chessList[5]->setBoardPosition(sf::Vector2f(0, 0));
		chessList[6]->setBoardPosition(sf::Vector2f(8, 0));

		chessList[7]->setBoardPosition(sf::Vector2f(1, 0));
		chessList[8]->setBoardPosition(sf::Vector2f(7, 0));

		chessList[9]->setBoardPosition(sf::Vector2f(1, 2));
		chessList[10]->setBoardPosition(sf::Vector2f(7, 2));

		chessList[11]->setBoardPosition(sf::Vector2f(0, 3));
		chessList[12]->setBoardPosition(sf::Vector2f(2, 3));
		chessList[13]->setBoardPosition(sf::Vector2f(4, 3));
		chessList[14]->setBoardPosition(sf::Vector2f(6, 3));
		chessList[15]->setBoardPosition(sf::Vector2f(8, 3));

	}
	else if (player.team == Team::Black) {
		
		chessList[0]->setBoardPosition(sf::Vector2f(4, 9));

		chessList[1]->setBoardPosition(sf::Vector2f(3, 9));
		chessList[2]->setBoardPosition(sf::Vector2f(5, 9));

		chessList[3]->setBoardPosition(sf::Vector2f(2, 9));
		chessList[4]->setBoardPosition(sf::Vector2f(6, 9));

		chessList[5]->setBoardPosition(sf::Vector2f(0, 9));
		chessList[6]->setBoardPosition(sf::Vector2f(8, 9));

		chessList[7]->setBoardPosition(sf::Vector2f(1, 9));
		chessList[8]->setBoardPosition(sf::Vector2f(7, 9));

		chessList[9]->setBoardPosition(sf::Vector2f(1, 7));
		chessList[10]->setBoardPosition(sf::Vector2f(7, 7));

		chessList[11]->setBoardPosition(sf::Vector2f(0, 6));
		chessList[12]->setBoardPosition(sf::Vector2f(2, 6));
		chessList[13]->setBoardPosition(sf::Vector2f(4, 6));
		chessList[14]->setBoardPosition(sf::Vector2f(6, 6));
		chessList[15]->setBoardPosition(sf::Vector2f(8, 6));
	}
}
//void Player::initialPlayer(Team _team)
//{
//	selectChess = nullptr;
//	selectPathChess = nullptr;
//	team = _team;
//	Factory chessFac;
//	Chess* tmpChess;
//
//	int tmpId = 0;
//	tmpChess = chessFac.getChess(Characters::King, team, tmpId++);
//	chessList.push_back(tmpChess);
//	for (int charIdx = int(Characters::Advisors); charIdx <= int(Characters::Cannons); charIdx++) {
//		for (int num = 0; num < 2; num++) {
//			tmpChess = chessFac.getChess(Characters(charIdx), team, tmpId++);
//			chessList.push_back(tmpChess);
//		}
//	}
//	for (int num = 0; num < 5; num++) {
//		tmpChess = chessFac.getChess(Characters::Soldiers, team, tmpId++);
//		chessList.push_back(tmpChess);
//	}
//	setChessInitPos(chessList, *this);
//}
//void Player::handleEvent(const sf::Event& event, ChessManager& commands) {
//
//}
//
//void Player::handleRealtimeInput(ChessManager& commands, Status status, Board& board) {
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//		if (status == Status::WaitBlackPressed || status == Status::WaitRedPressed) {
//			ChessCommand* cmd = new ChessFindPath(chessList, board, sf::Mouse::getPosition());
//			commands.setCommand(cmd);
//		}
//		else if (status == Status::WaitBlackPathPressed || status == Status::WaitRedPathPressed) {
//			ChessCommand* cmd = new ChessMove(validMoveChessList, board, sf::Mouse::getPosition());
//
//			commands.setCommand(cmd);
//		}
//	}
//}
//
//void Player::checkmate(const Player& opponent, const Board& board)
//{
//	//std::cout << "_____________________________\n";
//	bool find = false;
//	for (auto& tmpChess : this->chessList)
//	{
//		std::vector<sf::Vector2f> tmpPath;
//		if (tmpChess->getActive())
//		{
//			tmpPath = tmpChess->findPath(board);
//			for (auto& tmpPos : tmpPath)
//			{
//				//std::cout <<tmpChess->getId()<< "->" << tmpPos.x << " " << tmpPos.y << "\t" << opponent.getChessList()[0]->getPosition().x << " " << opponent.getChessList()[0]->getPosition().y << std::endl;
//				if (tmpPos == opponent.getChessList()[0]->getPosition())
//				{
//					find = true;
//					break;
//				}
//			}
//
//		}
//		if (find)
//			break;
//		
//	}
//	if (find)
//	{
//		std::cout << "Checkmate!!!!!!!!!!!!!!!!!!!!!\n";
//	}
//}
//
//// set chess initial position
//void setChessInitPos(std::vector<Chess*>& chessList, Player& player) {
//	if (player.team == Team::Red) {
//
//		chessList[0]->setPosition(sf::Vector2f(4, 0));
//
//		chessList[1]->setPosition(sf::Vector2f(3, 0));
//		chessList[2]->setPosition(sf::Vector2f(5, 0));
//
//		chessList[3]->setPosition(sf::Vector2f(2, 0));
//		chessList[4]->setPosition(sf::Vector2f(6, 0));
//
//		chessList[5]->setPosition(sf::Vector2f(0, 0));
//		chessList[6]->setPosition(sf::Vector2f(8, 0));
//
//		chessList[7]->setPosition(sf::Vector2f(1, 0));
//		chessList[8]->setPosition(sf::Vector2f(7, 0));
//
//		chessList[9]->setPosition(sf::Vector2f(1, 2));
//		chessList[10]->setPosition(sf::Vector2f(7, 2));
//
//		chessList[11]->setPosition(sf::Vector2f(0, 3));
//		chessList[12]->setPosition(sf::Vector2f(2, 3));
//		chessList[13]->setPosition(sf::Vector2f(4, 3));
//		chessList[14]->setPosition(sf::Vector2f(6, 3));
//		chessList[15]->setPosition(sf::Vector2f(8, 3));
//	}
//	else if (player.team == Team::Black) {
//		
//		chessList[0]->setPosition(sf::Vector2f(4, 9));
//
//		chessList[1]->setPosition(sf::Vector2f(3, 9));
//		chessList[2]->setPosition(sf::Vector2f(5, 9));
//
//		chessList[3]->setPosition(sf::Vector2f(2, 9));
//		chessList[4]->setPosition(sf::Vector2f(6, 9));
//
//		chessList[5]->setPosition(sf::Vector2f(0, 9));
//		chessList[6]->setPosition(sf::Vector2f(8, 9));
//
//		chessList[7]->setPosition(sf::Vector2f(1, 9));
//		chessList[8]->setPosition(sf::Vector2f(7, 9));
//
//		chessList[9]->setPosition(sf::Vector2f(1, 7));
//		chessList[10]->setPosition(sf::Vector2f(7, 7));
//
//		chessList[11]->setPosition(sf::Vector2f(0, 6));
//		chessList[12]->setPosition(sf::Vector2f(2, 6));
//		chessList[13]->setPosition(sf::Vector2f(4, 6));
//		chessList[14]->setPosition(sf::Vector2f(6, 6));
//		chessList[15]->setPosition(sf::Vector2f(8, 6));
//	}
//}
