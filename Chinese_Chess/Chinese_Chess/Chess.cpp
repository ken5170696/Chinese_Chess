#include "Chess.h"

Chess::Chess(const Team& _team) {
	active = true;
	team = _team;
	sprite.setScale(CHESS_IMG_SCALE, CHESS_IMG_SCALE);
}

King::King(const Team& _team)
	:Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_KING_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_KING_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Advisors::Advisors(const Team& _team)
	: Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_ADVISORS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_ADVISORS_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Minister::Minister(const Team& _team)
	: Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_MINISTER_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_MINISTER_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Chariots::Chariots(const Team& _team)
	:Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_CHARIOTS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_CHARIOTS_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Knights::Knights(const Team& _team)
	:Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_KNIGHTS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_KNIGHTS_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Cannons::Cannons(const Team& _team)
	: Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_CANNONS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_CANNONS_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Soldiers::Soldiers(const Team& _team)
	: Chess(_team)
{
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_SOLDIERS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_SOLDIERS_RED_IMG);
		sprite.setTexture(texture);
	}
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}

Chess* Factory::getChess(const Characters& ch, const Team& team)
{
	switch (ch)
	{
	case Characters::King: {
		return new King(team);
	}
	case Characters::Advisors: {
		return new Advisors(team);
	}case Characters::Minister: {
		return new Minister(team);
	}case Characters::Chariots: {
		return new Chariots(team);
	}case Characters::Knights: {
		return new Knights(team);
	}case Characters::Cannons: {
		return new Cannons(team);
	}case Characters::Soldiers: {
		return new Soldiers(team);
	}
	}
	return nullptr;
}

void King::move()
{

}

void Advisors::move()
{
}
void Minister::move()
{
}
void Chariots::move()
{
}
void Knights::move()
{
}
void Cannons::move()
{
}
void Soldiers::move()
{
}