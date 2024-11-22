#pragma once
#include "Objects/object.h"
#include <Characters/Animation/Animation.h>
#include <box2d/b2_body.h>

class Coin : public Object
{
public:
	~Coin();

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

	virtual void OnDestroy() override;

private:
	Animation animation;
	b2Body* body;

	void ManualPhysicDestroy();
};

