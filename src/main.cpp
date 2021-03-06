#include <iostream>
#include <map>
#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>
#include "Game/Screen/Title.h"

int screen_width = 32;
int screen_height = 24;
int tile_size = 16;

std::string path = "img";

int main(int argc, char** argv)
{

	printf("build time %s\n",__TIME__);

	path = argv[0];
	path = path.substr(0,path.rfind("/"));
	path = path.substr(0,path.rfind("/"));
	path += "/Resources";

	sf::RenderWindow window(sf::VideoMode(screen_width*tile_size, screen_height*tile_size), "TileGame",sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;

	Title game;
	Screen* currentScreen = &game;

	int elapsedTimeMS = 0;
	while (window.isOpen() && currentScreen != 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				currentScreen->handleEvent(event);
			}
		}
		if(elapsedTimeMS >0)
		{
			currentScreen->update(elapsedTimeMS);
		}

		window.setActive(true);
		window.clear(sf::Color::Black);
		currentScreen->display(&window);
		window.display();
		elapsedTimeMS = clock.restart().asMilliseconds();

		if(currentScreen->isScreenFinished())
		{
			currentScreen = currentScreen->getNextScreen();
		}

	}

	return 0;
}
