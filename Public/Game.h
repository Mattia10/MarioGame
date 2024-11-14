#pragma once
#include <SFML/Graphics.hpp>
#include "Rendering/Renderer.h"
#include "WindowCamera/Camera.h"

extern Camera camera;

void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& renderer);
