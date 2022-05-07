#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
	sf::RenderWindow w(sf::VideoMode(600, 800), "ok");
	sf::Event ev;
	while (w.isOpen())
	{
		while (w.pollEvent(ev))
		{
			switch (ev.type)
				case sf::Event::Closed:
					w.close();
					break;
		}
		w.clear();
		w.display();

	}
}