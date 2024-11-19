#pragma once
#include "Rendering/Renderer.h"
#include "Physics/Physics.h"
#include "Characters/Animation/Animation.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

	Animation runAnimation{};
	sf::Texture textureToDraw{};
	sf::Sound jumpSound{};

	b2Body* body{};
	size_t isGrounded = false;
	bool facingLeft = false;
};

