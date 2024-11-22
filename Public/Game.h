#pragma once
#include <SFML/Graphics.hpp>
#include "Rendering/Renderer.h"
#include "WindowCamera/Camera.h"
#include "Objects/Object.h"

extern Camera camera;

void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
void RenderUI(Renderer& renderer);

void QueueObjectForDestruction(Object* object);

void ManualDestroyObject(Object* object);
void DestroyQueuedObjects();