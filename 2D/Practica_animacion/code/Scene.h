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

	bool process_events(Window& window, b2World& physics_world, float window_height, float scale)
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::MouseButtonPressed:
				{
					b2Vec2 center = adapter.sfml_position_to_box2d_position
					(
						{ float(event.mouseButton.x), float(event.mouseButton.y) }, window_height, scale
					);

					//create_circle(physics_world, b2_dynamicBody, center.x, center.y, .5f);

					break;
				}

				case Event::Closed:
				{
					return true;
				}
			}
		}

		return false;
	}
};