#include "MultiplayerLobbyState.h"

MultiplayerLobby::MultiplayerLobby(StateStack& _stack, StateContext _context)
	:State(_stack, _context)
{
	sf::IpAddress serverAddr;
	sf::TcpListener listener;
	sf::TcpSocket tcpSocket;

	std::fstream ipFile(IPFILE);
	// 找到ipFIle為房主, 沒有表示不為房主
	if (ipFile) {

	}
	else {

	}
	ipFile.close();


	window = _context.window;
}

void MultiplayerLobby::draw()
{
}

bool MultiplayerLobby::update(sf::Time dt)
{
	return false;
}

bool MultiplayerLobby::handleEvent(const sf::Event& event)
{
	return false;
}

ServerMenu::ServerMenu(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
{
	window = _context.window;

	backgroundRect.setFillColor(sf::Color(100, 100, 100, 250));
	backgroundRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.8));
	backgroundRect.setOrigin(sf::Vector2f(backgroundRect.getLocalBounds().width / 2
		, backgroundRect.getLocalBounds().height / 2));
	backgroundRect.setPosition(sf::Vector2f(window->getSize().x * 0.5, window->getSize().y * 0.5));

	titleText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	titleText.setString(L"多人連線");
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Style::Bold);
	titleText.setCharacterSize(84);
	titleText.setOrigin(sf::Vector2f(titleText.getLocalBounds().width / 2
		, titleText.getLocalBounds().height / 2));
	titleText.setPosition(sf::Vector2f(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.2f));

	sf::Text playText;
	playText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	playText.setString(L"建立房間");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);

	sf::RectangleShape playRect;
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f);
	Button HostButton(OptionNames::Host, buttonPos, playRect, playText);
	mOptions.push_back(HostButton);

	playText.setString(L"加入房間");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos2(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 1.2);
	Button ClientButton(OptionNames::Client, buttonPos2, playRect, playText);
	mOptions.push_back(ClientButton);

	playText.setString(L"回主頁面");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos3(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 2.4);
	Button exitButton(OptionNames::Exit, buttonPos3, playRect, playText);
	mOptions.push_back(exitButton);
}

void ServerMenu::draw()
{
	window->draw(backgroundRect);
	window->draw(titleText);
	for (const auto& button : mOptions)
		window->draw(button);

}

bool ServerMenu::update(sf::Time dt)
{

	for (auto& button : mOptions)
		button.update();

	return true;
}

bool ServerMenu::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::Host) {
				requestStateClear();
				requestStackPush(States::ID::Menu);
			}
			if (button.getId() == OptionNames::Client) {
				requestStateClear();
				requestStackPush(States::ID::ServerEnterIpMenu);
			}
			else if (button.getId() == OptionNames::Exit) {
				requestStateClear();
				requestStackPush(States::ID::Menu);
			}
		}
	}

	return true;
}

ServerEnterIpMenu::ServerEnterIpMenu(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
{
	window = _context.window;

	backgroundRect.setFillColor(sf::Color(100, 100, 100, 250));
	backgroundRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.8));
	backgroundRect.setOrigin(sf::Vector2f(backgroundRect.getLocalBounds().width / 2
		, backgroundRect.getLocalBounds().height / 2));
	backgroundRect.setPosition(sf::Vector2f(window->getSize().x * 0.5, window->getSize().y * 0.5));

	titleText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	titleText.setString(L"輸入伺服器IP位置");
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Style::Bold);
	titleText.setCharacterSize(84);
	titleText.setOrigin(sf::Vector2f(titleText.getLocalBounds().width / 2
		, titleText.getLocalBounds().height / 2));
	titleText.setPosition(sf::Vector2f(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.2f));

	sf::Text playText;
	playText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	playText.setString(L"建立房間");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);

	sf::RectangleShape playRect;
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f * 1.2);
	Button SubmitButton(OptionNames::Submit, buttonPos, playRect, playText);
	mOptions.push_back(SubmitButton);

	sf::RectangleShape ipTextBoxRect;
	ipTextBoxRect.setSize(sf::Vector2f(window->getSize().x
		, window->getSize().y * 0.06f));
	ipTextBoxRect.setFillColor(sf::Color::White);
	sf::Vector2f ipTextBoxPos(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f);
	ipTextBox = new TextBox(0, ipTextBoxPos, ipTextBoxRect, "Enter ip address");
	ipTextBox->setTextColor(sf::Color::Black);
	ipTextBox->setTextFont(_context.fontHolder->get(Fonts::ID::BiauKai));

	playText.setString(L"回主頁面");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos3(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 2.4);
	Button exitButton(OptionNames::Exit, buttonPos3, playRect, playText);
	mOptions.push_back(exitButton);
}
void ServerEnterIpMenu::draw()
{
	window->draw(backgroundRect);
	window->draw(titleText);
	window->draw(*ipTextBox);
	for (const auto& button : mOptions)
		window->draw(button);
}

bool ServerEnterIpMenu::update(sf::Time dt)
{
	for (auto& button : mOptions)
		button.update();

	ipTextBox->update();

	return true;
}

bool ServerEnterIpMenu::handleEvent(const sf::Event& event)
{

	ipTextBox->handleEvent(*window, event);
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::Submit) {
				std::fstream ipFile;
				ipFile.open(IPFILE, std::ios_base::out);
				if (!ipFile)
				{
					std::cerr << "Can't open file!\n";
				}
				std::string ipStr = ipTextBox->getValue();
				bool illegal = false;
				for (const auto& ch : ipStr) {
					if (isalpha(ch)) {
						illegal = true;
						ipTextBox->clearText();
						break;
					}
				}
				ipFile << ipTextBox->getValue();
				ipFile.close();
				if (illegal) {
					continue;
				}
				requestStackPop();
				requestStackPush(States::ID::MultiplayerLobby);
			}
			else if (button.getId() == OptionNames::Exit) {

				std::remove(IPFILE);

				requestStackPop();
				requestStackPush(States::ID::Menu);
			}
		}
	}

	return true;
}
