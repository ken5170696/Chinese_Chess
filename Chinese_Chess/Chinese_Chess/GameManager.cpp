#include "GameManager.h"

const sf::Time GameManager::TimePerFrame = sf::seconds(1.f / 60.f);

GameManager::GameManager()
	:window(sf::VideoMode(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT),
		"Game1", sf::Style::Close | sf::Style::Titlebar )
	,stateStack(StateContext(&window, &fontHolder))
{
	window.setFramerateLimit(144);

	registerStates();
	stateStack.pushState(States::ID::Menu);

	fontHolder.load(Fonts::ID::BiauKai, FONT_FILE_PATH);
}

GameManager::~GameManager()
{

}

void GameManager::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
		
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvent();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (stateStack.isEmpty())
				window.close();
		}

		render();
	}
}

void GameManager::registerStates()
{
	/*stateStack.registerState<TitleStates>(States::ID::Title);*/
	stateStack.registerState<MenuState>(States::ID::Menu);
	//stateStack.registerState<MultiplayerGameState>(States::ID::MultiplayerGame);
	stateStack.registerState<ServerMenu>(States::ID::ServerMenu);
	stateStack.registerState<ServerEnterIpMenu>(States::ID::ServerEnterIpMenu);
	stateStack.registerState<MultiplayerGameState>(States::ID::MultiplayerLobby);
	stateStack.registerState<GameState>(States::ID::Game);
	stateStack.registerState<PauseState>(States::ID::Pause);
	stateStack.registerState<RedIsCeckMate>(States::ID::RedIsCheckMate);
	stateStack.registerState<BlackIsCheckMate>(States::ID::BlackIsCheckMate);
	stateStack.registerState<BlackIsStalemate>(States::ID::BlackIsStalemate);
	stateStack.registerState<RedIsStalemate>(States::ID::RedIsStalemate);


}

void GameManager::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameManager::update(sf::Time dt)
{
	stateStack.update(dt);
}

void GameManager::render()
{
	window.clear(sf::Color::White);

	stateStack.draw();

	window.display();
}
