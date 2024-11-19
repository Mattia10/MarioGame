#include "Characters/Mario.h"
#include "Rendering/Resources.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

constexpr float M_PI = 22.0f / 7.0f;

const float movementSpeed = 7.0f;
const float jumpVelocity = 10.0f;

void Mario::Begin()
{
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(0.5f, 0.5f);
	b2FixtureDef fixtureDef{};
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	b2CircleShape circleShape{};
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);

	circleShape.m_p.Set(0.0f, 0.5f);
	fixtureDef.userData.pointer = (uintptr_t)this;
	body->CreateFixture(&fixtureDef);
}

void Mario::Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		move *= 2;
	}

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isGrounded)
	{
		velocity.y = -jumpVelocity;
	}
	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void Mario::Draw(Renderer& renderer)
{
	renderer.Draw(Resources::textures["mario_idle.png"], position, sf::Vector2f(1.0f, 2.0f), angle);
}

void Mario::OnBeginContact()
{
	isGrounded = true;
}

void Mario::OnEndContact()
{
	isGrounded = false;

}
