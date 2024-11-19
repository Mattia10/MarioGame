#pragma once
#include "Rendering/Renderer.h"
#include "Objects/Object.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
	Map(float cellSize = 32.0f);

	void CreateCheckerBoard(size_t width, size_t height);
	sf::Vector2f InitFromImage(const sf::Image& image, std::vector<Object*>& objects);

	void Draw(Renderer& renderer);

	std::vector<std::vector<int>> grid;
	float cellSize;
};