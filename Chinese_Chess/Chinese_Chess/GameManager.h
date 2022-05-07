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
	void run();

private:
	void initWindow();
	void initVar();
	void pullEvent();

	void processEvent();
	void update();
	void render();
};

