#include "MultiplayerGameState.h"


MultiplayerGameState::MultiplayerGameState(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
	//, localBoard()
{
	std::cout << "Client Log: Starting\n";
	window = _context.window;

	std::fstream ipFile;
	ipFile.open(IPFILE, std::ios_base::in);
	if (!ipFile)
	{
		std::cerr << "Client Log: Can't open file!\n";
	}
	ipFile >> serverIp;
	std::cout << "Client Log: serverIp: " << serverIp << "\n";
	ipFile.close();

	clientSocket.setBlocking(false);
	isInit = false;
	isReady = false;
	localStatus = MutiplayerStatus::connecting;
	isConnected = false;
	background.setFillColor(sf::Color::White);
	background.setSize(sf::Vector2f(window->getSize()));
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - localBoard.getBoardSize().y) / 2);
	this->localBoard.setSpritePosition(tmpPos);
}

void MultiplayerGameState::draw()
{
	window->draw(background);
	window->draw(localBoard);
	for (const auto& tmpChess : LocalPlayer.getChessList()) {
		window->draw(*tmpChess);
	}
	for (const auto& tmpChess : RemotePlayer.getChessList()) {
		window->draw(*tmpChess);
	}
	if (selectedChess != nullptr && selectedChess->validSpot.size()) {
		for (const auto& validPathChess : selectedChess->validSpot)
		{
			if (validPathChess != nullptr)
			{
				window->draw(*validPathChess);
			}

		}
	}
}

bool MultiplayerGameState::update(sf::Time dt)
{
	if (isConnected == false) {
		std::fstream ipFile;
		if (clientSocket.connect(serverIp, SERVER_POST) != sf::Socket::Status::Disconnected) {
			std::cout << "Client Log:  --------------Connected\n";
			isConnected = true;
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
	sf::Packet sendPacket;
	sendPacket << unsigned int (Client::PacketType::None);
	clientSocket.send(sendPacket);

	sf::Packet packet;
	if (clientSocket.receive(packet) == sf::Socket::Done)
	{
		std::cout << "Client Log: Get packet\n";
		sf::Int32 packetType;
		packet >> packetType;
		switch (packetType)
		{
			case static_cast<sf::Int32>(Server::PacketType::InitialState) :
			{
				std::cout << "Client Log: Get InitialState\n";
				sf::Int32 playerTeam;
				packet >> playerTeam;
				std::cout << "Client Log: PlayerTeam: " << playerTeam << "\n";
				LocalPlayer = Player(Team(playerTeam));
				for (const auto& tmpChess : LocalPlayer.getChessList()) {
					tmpChess->setSpritePosition(localBoard.BoardToWindowPosition(tmpChess->getBoardPosition()));
				}
				break;
			}
			case static_cast<sf::Int32>(Server::PacketType::InitialRemotePlayer) :
			{
				std::cout << "Client Log: Get InitialRemotePlayer\n";
				sf::Int32 playerTeam;
				packet >> playerTeam;
				std::cout << "Client Log: RemotePlayerTeam: " << playerTeam << "\n";
				RemotePlayer = Player(Team(playerTeam));
				for (const auto& tmpChess : RemotePlayer.getChessList()) {
					tmpChess->setSpritePosition(localBoard.BoardToWindowPosition(tmpChess->getBoardPosition()));
				}
				break;
			}
			default:
				break;
		}
	}
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
