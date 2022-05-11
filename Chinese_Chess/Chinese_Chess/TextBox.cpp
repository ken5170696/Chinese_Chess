#include "TextBox.h"

TextBox::TextBox(int _id, sf::Vector2f _position, sf::RectangleShape _rect, std::string _placeholder)
{
	id = _id;
	placeholder = _placeholder;
	rect = _rect;
	outputText.setOrigin(outputText.getLocalBounds().width / 2,
		outputText.getLocalBounds().height * 0.5);
	rect.setOrigin(rect.getLocalBounds().width / 2,
		outputText.getLocalBounds().height / 2);

	outputText.setPosition(_position);
	rect.setPosition(_position);
	value = "";
	isActive = true;
}

void TextBox::clearText()
{
	value.clear();
}

void TextBox::setTextColor(const sf::Color& color)
{
	outputText.setFillColor(color);
}

void TextBox::setTextFont(const sf::Font& font)
{
	outputText.setFont(font);
}

void TextBox::update()
{

	outputText.setOrigin(sf::Vector2f(outputText.getLocalBounds().width / 2
		, outputText.getLocalBounds().height * 0.15));

	if (value.size()) {
		outputText.setString(value);
	}
	else {
		if (isOnFocus()) {
			outputText.setString(value);
		}
		else {
			outputText.setString(placeholder);
		}
	}
}

void TextBox::handleEvent(sf::RenderWindow& win, const sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (rect.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win)))) {
			textBoxStatus = unsigned int(textStatus::onFocus);
		}
		else {
			textBoxStatus = 0;
		}
	}
	if (isOnFocus()) {
		if (event.type == sf::Event::TextEntered) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				if (value.size())
					value.pop_back();
			}
			else {
				if (event.text.unicode < 128 && value.size() <= 20) {
					value.push_back(char(event.text.unicode));
				}
			}
		}
	}
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(outputText, states);
}
