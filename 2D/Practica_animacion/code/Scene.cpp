/**
* @file Scene.h
* @brief Implementación de Scene.hpp
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#include "Scene.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Rectangle_platform.h"
#include "Spin_rectangle.h"
#include "Basket.h"
#include "Fire.h"
#include "Player.h"
#include "Collision_sensor.h"

/// <summary>
/// Procesa el ciclo de la escena y los eventos de teclado
/// </summary>
void Scene::process_events() 
{
	Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
			{
				exit = true;
				break;
			}

			case Event::KeyPressed:
			{
				switch (event.key.code)
				{
					// Force inputs
					case Keyboard::Key::D:

						move_x = 0;

						// Recorre todos los objetos de geometries y ejecuta update_movement en los objetos Rectangle_Platform
						for (const auto& pair : geometries)
						{
							// Verifica si el objeto es de tipo Rectangle_Platform
							if (pair.second->get_type() == "Player_geo")
							{
								// Realiza un dynamic_cast para convertir el puntero base al tipo Rectangle_Platform
								Player* player_ref = dynamic_cast<Player*>(pair.second.get());

								// Verifica si la conversión fue exitosa antes de llamar a la función
								if (player_ref)
								{
									shared_ptr< Geometry > p_body = player_ref->get_player_body();

									move_x = 30.f;

									player_ref->body->ApplyForceToCenter({ (float)move_x, player_ref->get_position().y }, true);
								}
							}
						}

						break;

					case Keyboard::Key::A:

						move_x = 0;

						// Recorre todos los objetos de geometries y ejecuta update_movement en los objetos Rectangle_Platform
						for (const auto& pair : geometries)
						{
							// Verifica si el objeto es de tipo Rectangle_Platform
							if (pair.second->get_type() == "Player_geo")
							{
								// Realiza un dynamic_cast para convertir el puntero base al tipo Rectangle_Platform
								Player* player_ref = dynamic_cast<Player*>(pair.second.get());

								// Verifica si la conversión fue exitosa antes de llamar a la función
								if (player_ref)
								{
									shared_ptr< Geometry > p_body = player_ref->get_player_body();

									move_x = -30.f;

									player_ref->body->ApplyForceToCenter({ (float)move_x, player_ref->get_position().y }, true);
								}
							}
						}

						break;

					// CAR imput
					case Keyboard::Key::Q:

						break;

					// Jump imput
					case Keyboard::Key::E:

						break;

					// Platform Input
					case Keyboard::Key::Space:

						// Recorre todos los objetos de geometries y ejecuta update_movement en los objetos Rectangle_Platform
						for (const auto& pair : geometries)
						{
							// Verifica si el objeto es de tipo Rectangle_Platform
							if (pair.second->get_type() == "Rectangle_platform_geo")
							{
								// Realiza un dynamic_cast para convertir el puntero base al tipo Rectangle_Platform
								Rectangle_Platform* rectangle_plat_ref = dynamic_cast<Rectangle_Platform*>(pair.second.get());

								// Verifica si la conversión fue exitosa antes de llamar a la función
								if (rectangle_plat_ref)
								{
									rectangle_plat_ref->set_triggered();
									rectangle_plat_ref->update_movement(0.0016f);
								}
							}
						}

						break;
				}
			}
		}
	}
}

/// <summary>
/// Acciona todo el método create de los elementos del map de Geometries
/// </summary>
void Scene::create_scene() 
{
	// Todas las entidades definidas menos las que tienen giro tienen el siguiente orden de variables
	// 
	// Circle / Player : 
	//		BodyType, x, y, radius, density, scene*
	// 
	// Rectangle / Rectangle_Platform / Basket / Collision Sensor : 
	//		BodyType, x, y, width, height, scene*
	// 
	// Spin_rectangle : 
	//		BodyType, x, y, width, height, new_rotation, scene*

	geometries["PlayerCircle"] = Player::create(b2_dynamicBody, 5.f, 20.f, 2.f, 2.f, this);

	geometries["Rectangle_1"] = Rectangle::create(b2_kinematicBody, 0.f, 14.f, 11.75f, 20.f, this);
	geometries["Rectangle_1_Angle"] = Spin_Rectangle::create(b2_kinematicBody, 25.f, -1.f, 15.f, 20.f, 15.f, this);
	geometries["Rectangle_2"] = Rectangle::create(b2_kinematicBody, 20.f, 5.f, 40.f, 20.f, this);

	geometries["Collision_sensor_down"] = Collision_Sensor::create(b2_kinematicBody, 60.f, 40.f, 20.f, 35.f, this);

	geometries["Fire"] = Fire::create(b2_kinematicBody, 35.f, 10.f, 5.f, 5.f, this);

	geometries["Rectangle_1_up"] = Rectangle::create(b2_kinematicBody, 42.f + 6.f, 40.f, 12.f, 2.f, this);
	geometries["Rectangle_2_Angle"] = Spin_Rectangle::create(b2_kinematicBody, 45.f + 6.f, 38.f, 15.f, 2.f, 15.f, this);
	geometries["Rectangle_2_up"] = Rectangle::create(b2_kinematicBody, 22.f + 6.f, 30.f, 12.f, 2.f, this);

	geometries["Rectangle_platform_1"] = Rectangle_Platform::create(b2_kinematicBody, 60.f, 5.f, 20.f, 2.f, 35.f, this);
	geometries["Rectangle_platform_2"] = Rectangle_Platform::create(b2_kinematicBody, 15.f, 30.f, 13.f, 2.f, 12.f, this);

	// QUIERO HACER ALGO COMO ESTO --> geometries["Collision_sensor_down"].set_platform(geometries["Rectangle_platform_1"])

	geometries["Rectangle_basket_1"] = Basket::create(b2_kinematicBody, 7.f, 34.4f, 10.f, 2.f, 18.f, this);
	geometries["Rectangle_basket_2"] = Basket::create(b2_kinematicBody, 8.f, 33.f, 10.f, 2.f, 23.f, this);
}

/// <summary>
/// Se acciona el método reset_position() de todas las geometries
/// </summary>
void Scene::reset_scene() 
{
	for (auto& geometry : geometries)
	{
		geometry.second->reset_position();
	}
}

/// <summary>
/// Se pasa por todas las geometries y se ejecuta el método update
/// </summary>
void Scene::update() 
{
	for (const auto& pair : geometries)
	{
		pair.second->update();
	}
}

/// <summary>
/// Se pasa por todas las geometries y se ejecuta el método render
/// </summary>
void Scene::render() 
{
	for (auto& geometry : geometries)
	{
		geometry.second->render(*window);
	}
}