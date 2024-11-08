#include <SFML/Graphics.hpp>
#include "Game.h"
#include "WindowCamera/Camera.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mario Game");
	sf::Clock deltaClock;
	Camera camera;


	Begin(window);
	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.setView(camera.GetView(window.getSize()));
		Update(deltaTime);

		window.clear();

		// draw here
		Render(window);

		window.display();
	}
}












/*
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Mario Test");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
*/
