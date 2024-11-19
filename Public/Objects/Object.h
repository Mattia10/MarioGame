#pragma once
#include <Rendering/Renderer.h>

class Object
{
public:

	virtual void Begin() {};
	virtual void Update(float deltaTime) {};
	virtual void Render(Renderer& renderer) {};

	sf::Vector2f position{};
	float angle{};
};
