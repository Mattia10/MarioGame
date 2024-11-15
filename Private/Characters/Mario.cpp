#include "Characters/Mario.h"
#include <Physics/Physics.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

constexpr float M_PI = 22.0f / 7.0f;

const float movementSpeed = 3.0f;

void Mario::Begin()
{
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	body = Physics::world.CreateBody(&bodyDef);
	b2PolygonShape shape{};
	shape.SetAsBox(0.5f, 1.0f);

	b2FixtureDef fixtureDef{};
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
}

void Mario::Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		move *= 2;
	}

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void Mario::Draw(Renderer& renderer)
{
	renderer.Draw(Resources::textures["mario_idle.png"], position, sf::Vector2f(1.0f, 2.0f), angle);
}
