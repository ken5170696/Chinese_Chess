#include "Button.h"

Button::Button(int _id, sf::Vector2f _position, sf::RectangleShape _rect, sf::Text _text)
{
	id = _id;
	buttonText = _text;
	rect = _rect;
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2,
		buttonText.getLocalBounds().height / 2);
	rect.setOrigin(rect.getLocalBounds().width / 2,
		buttonText.getLocalBounds().height / 2);

	buttonText.setPosition(_position);
	rect.setPosition(_position);

	isActive = true;
}

bool Button::isHover() const
{
	return (buttonStatus & 1);
}

bool Button::isPressed() const
{
	return ((buttonStatus >> 1) & 1);
}

void Button::update()
{
	sf::Vector2f scale(1.f,1.f);
	if (isHover()) {
		scale = scale * 1.1f;
	}
	if (isPressed())
		rect.setFillColor(sf::Color::White);
	else
		rect.setFillColor(sf::Color(100, 100, 100, 50));
	//rect.setScale(scale);
	buttonText.setScale(scale);
}

void Button::handleEvent(sf::RenderWindow& win)
{
	if(isActive)
		buttonStatus = unsigned int(buttonStatus::active);
	
	if (rect.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win)))) {
		buttonStatus += unsigned int(buttonStatus::hover);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonStatus += unsigned int(buttonStatus::pressed);
		}
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(buttonText, states);
}
