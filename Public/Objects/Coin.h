#pragma once
#include "Objects/object.h"
#include <Characters/Animation/Animation.h>

class Coin : public Object
{
public:

	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& renderer) override;

private:
	Animation animation;
};

