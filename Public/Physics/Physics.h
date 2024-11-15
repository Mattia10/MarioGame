#pragma once

#include <box2d/b2_world.h>
#include <box2d/b2_draw.h>
#include <Rendering/Renderer.h>

class MyDebugDraw;

class Physics
{
public:
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);

	static b2World world;
	static MyDebugDraw* debugDraw;
};

