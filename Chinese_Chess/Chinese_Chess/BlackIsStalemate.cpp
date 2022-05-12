#include "BlackIsStalemate.h"
BlackIsStalemate::BlackIsStalemate(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
{
	window = _context.window;

	backgroundRect.setFillColor(sf::Color(100, 100, 100, 250));
	backgroundRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y * 0.8));
	backgroundRect.setOrigin(sf::Vector2f(backgroundRect.getLocalBounds().width / 2
		, backgroundRect.getLocalBounds().height / 2));
	backgroundRect.setPosition(sf::Vector2f(window->getSize().x * 0.5, window->getSize().y * 0.5));

	titleText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	titleText.setString(L"¶Â¤è¤í¦æ");
	titleText.setFillColor(sf::Color::Black);
	titleText.setStyle(sf::Text::Style::Bold);
	titleText.setCharacterSize(84);
	titleText.setOrigin(sf::Vector2f(titleText.getLocalBounds().width / 2
		, titleText.getLocalBounds().height / 2));
	titleText.setPosition(sf::Vector2f(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.2f));

	sf::Text playText;
	playText.setFont(_context.fontHolder->get(Fonts::ID::BiauKai));
	playText.setString(L"¦n!");
	playText.setCharacterSize(36);
	playText.setFillColor(sf::Color::Black);

	sf::RectangleShape playRect;
	playRect.setSize(sf::Vector2f(window->getSize().x
		, playText.getLocalBounds().height * 1.8f));
	playRect.setFillColor(sf::Color::White);
	sf::Vector2f buttonPos(_context.window->getSize().x / 2.f,
		_context.window->getSize().y * 0.5f);
	Button playButton(OptionNames::OK, buttonPos, playRect, playText);
	mOptions.push_back(playButton);
}

void BlackIsStalemate::draw()
{
	window->draw(backgroundRect);
	window->draw(titleText);
	for (const auto& button : mOptions)
		window->draw(button);
}

bool BlackIsStalemate::update(sf::Time dt)
{
	for (auto& button : mOptions)
		button.update();

	return true;
}

bool BlackIsStalemate::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::OK) {
				requestStackPop();
			}
		}
	}
	return true;
}
