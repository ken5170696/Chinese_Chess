#pragma once
#include <iostream>
#include <sstream>
#include "GameHeader.h"
#include "GameHeader.h"
class TextBox
	: public sf::Drawable
{
private:
	enum class textStatus
	{
		onFocus = 1,
	};
private:
	int id;
	sf::Text outputText;
	sf::RectangleShape rect;
	std::string placeholder;
	std::string value;
	bool isActive;
	unsigned int textBoxStatus;

public:
	TextBox(int _id, sf::Vector2f _position, sf::RectangleShape _rect, std::string _placeholder);

public:
	bool isOnFocus() {
		return (textBoxStatus & 1);
	};
	void clearText();
	void setTextColor(const sf::Color& color);
	void setTextFont(const sf::Font& font);
	int getId() const { return id; };
	std::string getValue() const { return value; };
	void update();
	void handleEvent(sf::RenderWindow& win, const sf::Event& event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};