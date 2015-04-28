#include <SFML/Graphics.hpp>
#include "Defines.h"

#include <vld.h>
#include "GameState.h"


int main()
{
    // create the window
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");
	window->setFramerateLimit(60);

	float maxTime = 1.f/60;
	sf::Clock deltaTimer;

	GameState g(window);

    //run the program as long as the window is open
    while (window->isOpen())
    {
		float deltaTime = deltaTimer.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
		}
		
		deltaTime = std::min(deltaTime, maxTime);
		g.handleInput();
		g.update(deltaTime);
        // clear the window with black color
        window->clear(sf::Color::Black);
		g.draw();
        // end the current frame
        window->display();
    }

	delete window;

    return 0;
}