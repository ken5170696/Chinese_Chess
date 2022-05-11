#include "MenuState.h"

MenuState::MenuState(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
	, menuView()
{
	window = _context.window;

	backgroundRect.setFillColor(sf::Color(100, 100, 100, 50));
	backgroundRect.setSize(sf::Vector2f(window->getSize().x * 0.6, window->getSize().y));
	backgroundRect.setOrigin(sf::Vector2f(backgroundRect.getLocalBounds().width / 2
		, backgroundRect.getLocalBounds().height / 2));
	backgroundRect.setPosition(sf::Vector2f(window->getSize().x * 0.5, window->getSize().y * 0.5));

	titleText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	titleText.setString(L"中國象棋");
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Style::Bold);
	titleText.setCharacterSize(84);
	titleText.setOrigin(sf::Vector2f(titleText.getLocalBounds().width / 2
		, titleText.getLocalBounds().height / 2));
	titleText.setPosition(sf::Vector2f(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.15f));

	sf::Text playText;
	playText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	playText.setString(L"開始遊戲");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);

	sf::RectangleShape playRect;
	playRect.setSize(sf::Vector2f(window->getSize().x * 0.6
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f);
	Button playButton(OptionNames::Play , buttonPos, playRect, playText);
	mOptions.push_back(playButton);

	playText.setString(L"多人遊戲");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x * 0.6
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos2(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 1.2);
	Button multButton(OptionNames::Multplayer, buttonPos2, playRect, playText);
	mOptions.push_back(multButton);

	playText.setString(L"離開遊戲");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);
	playRect.setSize(sf::Vector2f(window->getSize().x * 0.6
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos3(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f + playRect.getSize().y * 2.4);
	Button exitButton(OptionNames::Exit, buttonPos3, playRect, playText);
	mOptions.push_back(exitButton);

	menuView.objStack.push_back(&backgroundRect);
	menuView.objStack.push_back(&titleText);
	for (auto& button : mOptions)
		menuView.objStack.push_back(&button);
}

void MenuState::draw()
{
	menuView.draw(window);
}

bool MenuState::update(sf::Time dt)
{

	for (auto& button : mOptions)
		button.update();

	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::Play) {
				requestStackPop();
				requestStackPush(States::ID::Game);
			}
			else if (button.getId() == OptionNames::Multplayer) {
				requestStackPop();
				requestStackPush(States::ID::ServerMenu);
			}
			else if (button.getId() == OptionNames::Exit) {
				requestStackPop();
			}
		}
	}
	
	return true;
}
