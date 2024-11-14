#include "Game.h"
#include "Rendering/Resources.h"
#include "Map.h"

#include <filesystem>

//sf::CircleShape circle(2.0f, 360u);

Map map(16.0f);
Camera camera(320.0f);

const float movementSpeed = 100.0f;

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

	sf::Image image;
	image.loadFromFile(path + "map.png");
	map.InitFromImage(image);

	camera.position = sf::Vector2f(160.0f, 160.0f);
}

void Update(float deltaTime)
{

	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		move *= 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera.position.x += move * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera.position.x -= move * deltaTime;
	}
}

void Render(Renderer& renderer)
{
	map.Draw(renderer);
}
