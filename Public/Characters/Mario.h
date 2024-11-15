#pragma once
#include "Rendering/Renderer.h"
#include "Rendering/Resources.h"

#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

class Mario
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	sf::Vector2f position{};
	float angle{};

private:
	b2Body* body;
};

