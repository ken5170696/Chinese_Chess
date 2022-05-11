#include "MenuView.h"

void MenuView::draw(sf::RenderWindow* window)
{
	for (const auto& obj : objStack)
		window->draw(*obj);
}
