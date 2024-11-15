#include "Game.h"
#include "Rendering/Resources.h"
#include "Map.h"
#include "Physics/Physics.h"

#include <filesystem>
#include <Characters/Mario.h>

//sf::CircleShape circle(2.0f, 360u);

Map map(1.0f);
Camera camera(20.0f);
Mario mario;

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

	Physics::Init();

	sf::Image image;
	image.loadFromFile(path + "map.png");
	mario.position = map.InitFromImage(image);
	mario.Begin();

}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);

	mario.Update(deltaTime);

	camera.position = mario.position;
}

void Render(Renderer& renderer)
{
	map.Draw(renderer);
	mario.Draw(renderer);

	Physics::DebugDraw(renderer);
}
