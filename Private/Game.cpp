#include "Characters/Mario.h"
#include "Game.h"
#include "Rendering/Resources.h"
#include "Map.h"
#include "Physics/Physics.h"

#include <filesystem>
#include <SFML/Audio.hpp>

//sf::CircleShape circle(2.0f, 360u);

Map map(1.0f);
Camera camera(20.0f);
Mario mario;
std::vector<Object*> objects{};

std::string texturePath = "./Textures/";
std::string soundPath = "./Sounds/";

sf::Music music{};

void Begin(const sf::Window& window)
{
	/*circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setFillColor(sf::Color::Red);*/

	//folder path

	for (auto& file : std::filesystem::directory_iterator(texturePath))
	{
		if (file.is_regular_file() && file.path().extension() == ".png")
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	for (auto& file : std::filesystem::directory_iterator(soundPath))
	{
		if (file.is_regular_file() && (file.path().extension() == ".ogg" || 
			file.path().extension() == ".wav"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	music.openFromFile(soundPath + "music.ogg");
	music.setLoop(true);
	music.setVolume(50);
	
	Physics::Init();

	sf::Image image;
	image.loadFromFile(texturePath + "map.png");
	mario.position = map.InitFromImage(image, objects);
	mario.Begin();

	for (auto& object : objects)
	{
		object->Begin();
	}

	music.play();
}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);

	mario.Update(deltaTime);
	camera.position = mario.position;

	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}
}

void Render(Renderer& renderer)
{
	renderer.Draw(Resources::textures["sky.png"], camera.position, camera.GetViewSize());
	map.Draw(renderer);

	for (auto& object : objects)
	{
		object->Render(renderer);
	}

	mario.Draw(renderer);

	Physics::DebugDraw(renderer);
}
