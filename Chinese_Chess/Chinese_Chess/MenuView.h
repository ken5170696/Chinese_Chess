#pragma once
#include "GameHeader.h"
#include <iostream>
#include <vector>
class MenuView
{
public:
	std::vector<sf::Drawable*> objStack;
	void draw(sf::RenderWindow* window);
};

