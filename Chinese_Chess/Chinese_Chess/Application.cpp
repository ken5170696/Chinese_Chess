#include "Application.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	:window(sf::VideoMode(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT),
		"Game1", sf::Style::Close | sf::Style::Titlebar )
	,stateStack(StateContext(&window, &fontHolder))
{
	window.setFramerateLimit(144);

	registerStates();
	stateStack.pushState(States::ID::Menu);

	fontHolder.load(Fonts::ID::BiauKai, FONT_FILE_PATH);
}

Application::~Application()
{

}

void Application::run()
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

void Application::registerStates()
{
	/*stateStack.registerState<TitleStates>(States::ID::Title);*/
	stateStack.registerState<MenuState>(States::ID::Menu);
	stateStack.registerState<GameState>(States::ID::Game);
	stateStack.registerState<PauseState>(States::ID::Pause);
}

void Application::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Application::update(sf::Time dt)
{
	stateStack.update(dt);
}

void Application::render()
{
	window.clear(sf::Color::White);

	stateStack.draw();

	window.display();
}
