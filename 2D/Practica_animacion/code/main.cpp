// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#include "Scene.h"
#include <SFML/Window.hpp>

int main()
{
	// Se define como de grande es la pantalla
	constexpr auto window_width = 800u;
	constexpr auto window_height = 600u;

	RenderWindow window(sf::VideoMode(window_width, window_height), "Práctica de animación", sf::Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	Scene scene (window);

	scene.run();

	return 0;
}