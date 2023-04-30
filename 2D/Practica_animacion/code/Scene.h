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

#include <memory>
#include "Geometry.h"
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Scene
{
	vector < shared_ptr<Geometry> > geometries;
	//map < string, shared_ptr<Geometry> > geometries;

	b2World world;

	float physics_to_graphics_scale = 100.f;

	RenderWindow* window;

public:

	Scene(const RenderWindow& given_window) : world(b2Vec2(0.0f, -10.0f))
	{
		window = const_cast<RenderWindow*>(&given_window);
	}

	Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position)
	{
		return Vector2f(box2d_position.x * physics_to_graphics_scale, window->getSize().y - box2d_position.y * physics_to_graphics_scale);
	}

	void run()
	{
		bool exit = false;

		do
		{
			process_events();

			//"moving_platform".update_movement()
			//"moving_platform".detect_ball()

			window->clear();

			render();

			window->display();

			//...

		} while (!exit);
	}


private:

	void render()
	{
		for (auto& geometry : geometries)
		{
			//geometry.second->render(*window);
			geometry->render(*window);
		}
	}

	void create_scene();		// crear todos los elementos de la escena

	void process_events();

};