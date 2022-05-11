#pragma once
#include <iostream>
#include "GameHeader.h"
class Button
	: public sf::Drawable
{
private:
	enum class buttonStatus
	{
		hover = 1,
		pressed = 1 << 1,
		active = 1 << 2,
	};
private:
	int id;
	sf::Text buttonText;
	sf::RectangleShape rect;
	bool isActive;
	unsigned int buttonStatus;

public:
	Button(int _id, sf::Vector2f _position, sf::RectangleShape _rect, sf::Text _text);

public:
	bool isHover() const;
	bool isPressed() const;
	int getId() const { return id; };
	void update();
	void handleEvent(sf::RenderWindow& win);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};