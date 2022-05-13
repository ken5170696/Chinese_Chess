#include "GameManager.h"

const sf::Time GameManager::TimePerFrame = sf::seconds(1.f / 144.f);

GameManager::GameManager()
	:window(sf::VideoMode(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT),
		"Game1", sf::Style::Close | sf::Style::Titlebar )
	,stateStack(StateContext(&window, &fontHolder, &textureHolder))
{
	pause = false;
	window.setFramerateLimit(144);

	registerStates();
	stateStack.pushState(States::ID::Menu);

	fontHolder.load(Fonts::ID::BiauKai, FONT_FILE_PATH);
	textureHolder.load(Textures::ID::CheckBoard, CHECKBOARD_IMG);
	textureHolder.load(Textures::ID::Chess_King_Black,		CHESS_KING_BLACK_IMG	);
	textureHolder.load(Textures::ID::Chess_King_Red,		CHESS_KING_RED_IMG		);
	textureHolder.load(Textures::ID::Chess_Advisors_Black,	CHESS_ADVISORS_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Advisors_Red,	CHESS_ADVISORS_RED_IMG	);
	textureHolder.load(Textures::ID::Chess_Minister_Black,	CHESS_MINISTER_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Minister_Red,	CHESS_MINISTER_RED_IMG	);
	textureHolder.load(Textures::ID::Chess_Chariots_Black,	CHESS_CHARIOTS_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Chariots_Red,	CHESS_CHARIOTS_RED_IMG);
	textureHolder.load(Textures::ID::Chess_Knights_Black,	CHESS_KNIGHTS_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Knights_Red,		CHESS_KNIGHTS_RED_IMG	);
	textureHolder.load(Textures::ID::Chess_Cannons_Black,	CHESS_CANNONS_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Cannons_Red,		CHESS_CANNONS_RED_IMG	);
	textureHolder.load(Textures::ID::Chess_Soldiers_Black,	CHESS_SOLDIERS_BLACK_IMG);
	textureHolder.load(Textures::ID::Chess_Soldiers_Red,	CHESS_SOLDIERS_RED_IMG)	;
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
	stateStack.registerState<MenuState>(			States::ID::Menu);
	stateStack.registerState<MultiplayerGameState>(	States::ID::MultiplayerGame);
	stateStack.registerState<MutiplayerMenu>(		States::ID::ServerMenu);
	stateStack.registerState<ServerEnterIpMenu>(	States::ID::ServerEnterIpMenu);
	stateStack.registerState<MultiplayerGameState>(	States::ID::MultiplayerMenu);
	stateStack.registerState<GameState>(			States::ID::Game);
	stateStack.registerState<PauseState>(			States::ID::Pause);
	stateStack.registerState<RedIsCheckMate>(		States::ID::RedIsCheckMate);
	stateStack.registerState<BlackIsCheckMate>(		States::ID::BlackIsCheckMate);
	stateStack.registerState<BlackIsStalemate>(		States::ID::BlackIsStalemate);
	stateStack.registerState<RedIsStalemate>(		States::ID::RedIsStalemate);


}

void GameManager::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		if (pause == false)
			stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::GainedFocus)
			pause = false;
		if (event.type == sf::Event::LostFocus)
			pause = true;
	}
}

void GameManager::update(sf::Time dt)
{
	if(pause == false)
		stateStack.update(dt);
}

void GameManager::render()
{
	window.clear(sf::Color::White);

	stateStack.draw();

	window.display();
}
