#include "Map.h"
#include "Rendering/Resources.h"
#include "Objects/Coin.h"
#include "Objects/Object.h"

#include <box2d/b2_body.h>
#include <Physics/Physics.h>
#include <box2d/b2_polygon_shape.h>

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}

void Map::CreateCheckerBoard(size_t width, size_t height)
{
	grid = std::vector(width, std::vector(height, 0));

	bool last = 0;

	for (auto& column : grid)
	{
		for (auto& cell : column)
		{
			last = cell = !last;
		}

		if (width % 2 == 0)
		{
			last = !last;
		}
	}
}

void Map::Draw(Renderer& renderer)
{
	int x = 0;
	for (const auto& column : grid)
	{
		int y = 0;
		for (const auto& cell : column)
		{
			if (cell)
			{
				renderer.Draw(Resources::textures["brick.png"], 
					sf::Vector2f(cellSize * x + cellSize / 2.0f,
						cellSize * y + cellSize / 2.0f),
					sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}

sf::Vector2f Map::InitFromImage(const sf::Image& image, std::vector<Object*>& objects)
{
	grid.clear();
	grid = std::vector(image.getSize().x, std::vector(image.getSize().y, 0));

	sf::Vector2f marioPosition{};

	for (size_t x = 0; x < grid.size(); x++)
	{
		for (size_t y = 0; y < grid[x].size(); y++)
		{
			sf::Color color = image.getPixel(x, y);
			if (color == sf::Color::Black)
			{
				grid[x][y] = 1;
				b2BodyDef bodyDef{};
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);

				b2Body* body = Physics::world.CreateBody(&bodyDef);
				b2PolygonShape shape{};
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);
				body->CreateFixture(&shape, 0.0f);
			}
			else if (color == sf::Color::Red)
			{
				marioPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
			}
			else if (color == sf::Color::Yellow)
			{
				Object* coin = new Coin();
				coin->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
					cellSize * y + cellSize / 2.0f);
				objects.push_back(coin);
			}
		}

	}

	return marioPosition;
}
