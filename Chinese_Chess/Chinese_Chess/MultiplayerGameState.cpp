#include "MultiplayerGameState.h"


MultiplayerGameState::MultiplayerGameState(StateStack& _stack, StateContext _context)
    : State(_stack, _context)
    , localBoard()
{
    window = _context.window;
	std::fstream ipFile;
	ipFile.open(IPFILE, std::ios_base::in);
	if (!ipFile)
	{
		std::cerr << "Can't open file!\n";
	}
	ipFile >> serverIp;
	ipFile.close();
	clientSocket.setBlocking(false);
	clientSocket.connect(serverIp, SERVER_POST);
    isInit = false;
    isReady = false;
	localStatus = MutiplayerStatus::connecting;

	background.setFillColor(sf::Color::White);
	background.setSize(sf::Vector2f(window->getSize()));
}

void MultiplayerGameState::draw()
{
	window->draw(background);
}

bool MultiplayerGameState::update(sf::Time dt)
{
	if (isConnected == false) {
		if (clientSocket.connect(serverIp, SERVER_POST) == sf::TcpSocket::Done) {
			isConnected == true;
		}
		return true;
	}
	handleIncomingPackets();
    return true;
}

bool MultiplayerGameState::handleEvent(const sf::Event& event)
{
    return true;
}

void MultiplayerGameState::handleIncomingPackets()
{
}

sf::Time MultiplayerGameState::now() const
{
	return localClock.getElapsedTime();
}

MultiplayerGameState::ConnectingState::ConnectingState(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
{
	window = _context.window;

	backgroundRect.setFillColor(sf::Color(100, 100, 100, 250));
	backgroundRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.8));
	backgroundRect.setOrigin(sf::Vector2f(backgroundRect.getLocalBounds().width / 2
		, backgroundRect.getLocalBounds().height / 2));
	backgroundRect.setPosition(sf::Vector2f(window->getSize().x * 0.5, window->getSize().y * 0.5));

	titleText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	titleText.setString(L"連線中...");
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Style::Bold);
	titleText.setCharacterSize(84);
	titleText.setOrigin(sf::Vector2f(titleText.getLocalBounds().width / 2
		, titleText.getLocalBounds().height / 2));
	titleText.setPosition(sf::Vector2f(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.2f));

	sf::Text playText;
	sf::RectangleShape playRect;

	playText.setString(L"回主頁面");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos2(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 1.2);
	Button exitButton(OptionNames::Exit, buttonPos2, playRect, playText);
	mOptions.push_back(exitButton);
}

void MultiplayerGameState::ConnectingState::draw()
{
	window->draw(backgroundRect);
	window->draw(titleText);
	for (const auto& button : mOptions)
		window->draw(button);
}

bool MultiplayerGameState::ConnectingState::update(sf::Time dt)
{

	for (auto& button : mOptions) {
		button.update();
	}

	return true;
}

bool MultiplayerGameState::ConnectingState::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::Exit) {
				requestStateClear();
				requestStackPush(States::ID::Menu);
			}
		}
	}

	return true;
}
