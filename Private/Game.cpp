#include "Characters/Mario.h"
#include "Game.h"
#include "Rendering/Resources.h"
#include "Map.h"
#include "Physics/Physics.h"

#include <filesystem>
#include <SFML/Audio.hpp>

std::vector<Object*> ObjectsToDestroy;

Map map(1.0f);
Camera camera(20.0f);
Mario mario;
std::vector<Object*> objects{};
sf::Image mapImage{};

bool paused = false;
sf::RectangleShape backgroudShape(sf::Vector2f(1.0f, 1.0f));

std::string texturePath = "./Textures/";
std::string soundPath = "./Sounds/";
std::string fontPath = "./Fonts/"; 

sf::Music music{};

sf::Font font{};
sf::Text coinsText("Coins", font);

void Restart()
{
	Physics::Init();

	mario = Mario();


	//hard reset, need to find a better way
	for (auto& object : objects)
	{
		if (object)
			ManualDestroyObject(object);
	}

	mario.position = map.InitFromImage(mapImage, objects);

	mario.isDead = false;
	paused = false;

	mario.Begin();

	for (auto& object : objects)
	{
		object->Begin();
	}

	music.play();
}

void Begin()
{
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

	font.loadFromFile(fontPath + "font.ttf");
	coinsText.setFillColor(sf::Color::White);
	coinsText.setOutlineColor(sf::Color::Black);
	coinsText.setOutlineThickness(1.0f);
	coinsText.setScale(0.1f, 0.1f);

	backgroudShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroudShape.setOrigin(0.5f, 0.5f);

	mapImage.loadFromFile(texturePath + "map.png");

	Restart();
}

void Update(float deltaTime)
{
	if (mario.isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Restart();
	}

	if (mario.isDead || paused)
		return;

	Physics::Update(deltaTime);
	mario.Update(deltaTime);
	camera.position = mario.position;

	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}

	DestroyQueuedObjects();
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

void RenderUI(Renderer& renderer)
{
	coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
	coinsText.setString("Coins: " + std::to_string(mario.GetCoins()));
	renderer.target.draw(coinsText);

	if (paused || mario.isDead)
	{
		backgroudShape.setScale(camera.GetViewSize());
		renderer.target.draw(backgroudShape);
	}
}

void QueueObjectForDestruction(Object* object)
{
	ObjectsToDestroy.push_back(object);
}

void DestroyQueuedObjects()
{
	for (Object* object : ObjectsToDestroy)
	{
		const auto& it = std::find(objects.begin(), objects.end(), object);
		if (it != objects.end())
		{
			delete* it;
			objects.erase(it);
		}
	}
	ObjectsToDestroy.clear();
}

void ManualDestroyObject(Object* object)
{
	const auto& it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end())
	{
		delete* it;
		objects.erase(it);
	}
}
