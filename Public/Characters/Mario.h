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

	size_t GetCoins() { return coins; }

	// Inherited via ContactListener
	void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
	void OnEndContact(b2Fixture* self, b2Fixture* other) override;

	sf::Vector2f position{};
	float angle{};
	bool isDead{};

private:

	FixtureData fixtureData{};
	b2Body* body{};
	b2Fixture* groundFixture;

	Animation runAnimation{};
	sf::Texture textureToDraw{};
	sf::Sound jumpSound{};

	size_t isGrounded = false;
	bool facingLeft = false;

	size_t coins{};
};

