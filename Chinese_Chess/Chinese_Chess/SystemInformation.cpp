#include "SystemInformation.h"
#include <iostream>

SystemInformation::SystemInformation()
{
	fontSize = 55;
	if (font.loadFromFile(FONT_FILE_PATH))
	{
	
		sf::Text tmpRed, tmpBlack;
		nameOfRed.setFont(font);
		nameOfRed.setFillColor(sf::Color::Red);
		nameOfRed.setCharacterSize(fontSize);
		nameOfRed.setPosition(WINDOW_RESOLUTION_WIDTH * 0.6, WINDOW_RESOLUTION_HEIGHT * 0.02);
		

		nameOfBlack.setFont(font);
		nameOfBlack.setFillColor(sf::Color::Black);
		nameOfBlack.setCharacterSize(fontSize);
		nameOfBlack.setPosition(WINDOW_RESOLUTION_WIDTH * 0.6, WINDOW_RESOLUTION_HEIGHT * 0.52);


		arrow.setFont(font);
		arrow.setCharacterSize(fontSize);
		arrow.setString("=>");
	}
}
sf::Text SystemInformation::get()
{
	return nameOfRed;
}
void SystemInformation::setArrow(bool flag)
{
	if (flag)
	{
		arrow.setFillColor(sf::Color::Black);
		arrow.setPosition(WINDOW_RESOLUTION_WIDTH * 0.6 - fontSize, WINDOW_RESOLUTION_HEIGHT * 0.52);
	}
	else
	{
		arrow.setFillColor(sf::Color::Red);
		arrow.setPosition(WINDOW_RESOLUTION_WIDTH * 0.6 - fontSize, WINDOW_RESOLUTION_HEIGHT * 0.02);
	}
}
void SystemInformation::draw(sf::RenderWindow* window)
{
	
	window->draw(arrow);
	window->draw(nameOfRed);
	window->draw(nameOfBlack);
}

void SystemInformation::setName(sf::String _nameOfRed, sf::String _nameOfBlack)
{
	nameOfRed.setString( _nameOfRed);
	nameOfBlack.setString(_nameOfBlack);
}
