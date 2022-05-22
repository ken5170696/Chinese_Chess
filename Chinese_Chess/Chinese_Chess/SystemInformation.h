#pragma once
#include "GameHeader.h"
class SystemInformation
{
private:
	sf::Text nameOfRed;
	sf::Text nameOfBlack;
	sf::Font font;
	sf::Text arrow;
	int fontSize;
public:
	SystemInformation();

	sf::Text get();
	//True is Black turn
	//False is Red turn 
	void setArrow(bool flag);
	void draw(sf::RenderWindow* window);
	void setName(sf::String _nameOfRed, sf::String _nameOfBlack);
};

