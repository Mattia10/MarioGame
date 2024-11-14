#include "Game.h"
#include "Rendering/Resources.h"
#include "Map.h"

#include <filesystem>

//sf::CircleShape circle(2.0f, 360u);

Map map;
Camera camera(320.0f);

void Begin(const sf::Window& window)
{
	/*circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setFillColor(sf::Color::Red);*/

	//folder path
	std::string path = "./Textures/";

	for (auto& file : std::filesystem::directory_iterator(path))
	{
		if (file.is_regular_file() && file.path().extension() == ".png")
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	map.CreateCheckerBoard(10, 10);
	camera.position = sf::Vector2f(160.0f, 160.0f);
}

void Update(float deltaTime)
{

}

void Render(Renderer& renderer)
{
	map.Draw(renderer);
}
