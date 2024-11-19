#pragma once
#include "Rendering/Renderer.h"
#include "Physics/Physics.h"

#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

class Mario : public ContactListener
{
public:
	void Begin();
	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	// Inherited via ContactListener
	void OnBeginContact() override;
	void OnEndContact() override;

	sf::Vector2f position{};
	float angle{};

private:
	b2Body* body{};
	bool isGrounded = false;
};

