#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(float zoomLevel = 5.0f);
	sf::View GetView(sf::Vector2u windowSize);
	sf::Vector2f GetViewSize();

	float zoomLevel;
	sf::Vector2f position;

private:

	sf::Vector2f viewSize{};
};

