#pragma once
#include "Objects/Object.h"
#include "Animation/Animation.h"
#include "Physics/Physics.h"

class Enemy : public Object
{
public:

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

	void Die();

private:
	Animation animation{};
	float movement = 5.0f;

	float destroyTimer = 0.0f;
	bool isDead = false;

	FixtureData fixtureData{};
	b2FixtureDef fixtureDef{};
	b2Body* body{};
};

