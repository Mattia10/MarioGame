#include "Game.h"

sf::CircleShape circle(2.0f, 360u);

void Begin(const sf::Window& window)
{
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setFillColor(sf::Color::Red);
}

void Update(float deltaTime)
{

}

void Render(sf::RenderWindow& window)
{
	window.draw(circle);
}
