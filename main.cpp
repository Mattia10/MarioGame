#include <SFML/Graphics.hpp>

#include "Game.h"
#include "WindowCamera/Camera.h"
#include "Rendering/Renderer.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario Game");
	sf::Clock deltaClock;

	Renderer renderer(window);

	window.setFramerateLimit(60);

	Begin();
	while (window.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				std::cout << "button pressed2" << std::endl;
				paused = !paused;
			}
		}

		Update(deltaTime);
		
		window.clear();

		window.setView(camera.GetView(window.getSize()));
		Render(renderer);

		window.setView(camera.GetUIView());
		RenderUI(renderer);

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
