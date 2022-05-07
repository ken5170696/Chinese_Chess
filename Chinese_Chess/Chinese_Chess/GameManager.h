#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>



class Game
{
private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;
public:
	Game();
	~Game();


	void initWindow();
	void initVar();
	void pullEvent();
	bool windowIsOpen();

	void update();
	void render();
};

