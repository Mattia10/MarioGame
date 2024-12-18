#pragma once
#include <Rendering/Renderer.h>

class Object
{
public:

	virtual void Begin() {};
	virtual void Update(float deltaTime) {};
	virtual void Render(Renderer& renderer) {};

	virtual void OnDestroy() {};

	std::string tag{};

	sf::Vector2f position{};
	float angle{};
};

