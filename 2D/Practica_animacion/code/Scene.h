//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
//

#pragma once

#include "Adapter.h"
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class Scene 
{
	Adapter adapter;

	vector < Geometry > bodies;

	// Esto configra la gravedad de la escena
	b2World gravity_physics_world{ b2Vec2{ 0, -10.f } };

public:

	Scene(float given_x_gravity, float given_y_gravity)
	{
		set_gravity_world(b2Vec2{ given_x_gravity, given_y_gravity });
	}

	void set_gravity_world(b2Vec2 gravity)
	{
		gravity_physics_world.SetGravity(gravity);
	}

	b2World & get_gravity_physics_world() 
	{
		return gravity_physics_world;
	}

	// ------------------------------------------------------------------------------------------ //

	void create_scene() 
	{

	}

	void run() 
	{
		do
		{
			timer.restart();

			// Process window events:

			exit = scene.process_events(window, scene.get_gravity_physics_world(), window_height, physics_to_graphics_scale);

			// Update:

			scene.get_gravity_physics_world().Step(delta_time, 8, 4);

			// Render:

			window.clear();

			geo.render(scene.get_gravity_physics_world(), window, physics_to_graphics_scale, Color::Blue);

			window.display();

			// Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
			// fotogramas por segundo deseada:

			float elapsed = timer.getElapsedTime().asSeconds();

			if (elapsed < target_time)
			{
				sleep(seconds(target_time - elapsed));
			}

			// Se restablece la estimación de la duración del siguiente fotograma:

			delta_time = timer.getElapsedTime().asSeconds();
		} while (!exit);
	}

	bool process_events(Window& window, b2World& physics_world, float window_height, float scale)
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
				{
					return true;
				}

				case Event::KeyPressed:
				{
					switch (event.key.code)
					{
						// Force inputs
						case Keyboard::Key::A:
							break;

						case Keyboard::Key::D:
							break;

						// Jump imput
						case Keyboard::Key::Space:
							break;
					}
				}
			}
		}

		return false;
	}
};