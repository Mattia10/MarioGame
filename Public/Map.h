#pragma once
#include "Rendering/Renderer.h"

#include <vector>

class Map
{
public:
	Map(float cellSize = 32.0f);
	void CreateCheckerBoard(size_t width, size_t height);
	void Draw(Renderer& renderer);

	std::vector<std::vector<int>> grid;
	float cellSize;
};