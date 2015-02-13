//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Window/Event.hpp>
//#include <SFML/Graphics/CircleShape.hpp>
#include <sfml.h>
#include "Game.h"
using namespace sf;
static void loop(RenderWindow& window);
int main()
{
	// Luodaan ikkuna pelille
	{
		RenderWindow window(VideoMode(1920, 1200), "SFML works!");
		loop(window);

		return 0;
		
	}
}
static void loop(RenderWindow& window)
{
	// Pyöritetään pelin päälooppia
	Clock clock;
	Time elapsed_Time;
	Event event;
	Game game(window.getSize());

	while (window.isOpen())
	{
		elapsed_Time = clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		game.update(elapsed_Time);
		game.draw(window);
		window.display();
	}
}