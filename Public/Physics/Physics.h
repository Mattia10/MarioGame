#pragma once

#include <box2d/b2_world.h>
#include <Rendering/Renderer.h>
#include <box2d/b2_fixture.h>
#include <set>

class MyDebugDraw;
class Mario;
class Object;

class ContactListener
{
public:
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Mario,
	MapTile,
	Object
};

struct FixtureData
{
	ContactListener* listener;
	FixtureDataType type;

	union
	{
		Mario* mario;
		Object* object;
		struct { int mapX, mapY; };
	};
};

class Physics
{
public:
	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& renderer);

	static void QueueBodyForDestruction(b2Body* body);

	static b2World world;
	static MyDebugDraw* debugDraw;

private:

	static void SafeDestroyBody(b2Body* body);
	static void DestroyQueuedBodies();

	static std::set<std::pair<b2Fixture*, b2Fixture*>> activeContacts;

};

