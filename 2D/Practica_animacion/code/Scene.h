/**
* @file Scene.h
* @brief Encargada del manejo de todo el ciclo de juego además de la creación de los elementos de geometry
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04


#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "ContactListener.h"

using namespace sf;
using namespace std;

// Método para evitar la doble inclusión al necesitar la referencia a geometry
class Geometry;

/// <summary>
/// Encargada del manejo de toda la escena
/// </summary>
class Scene
{
	map < string, shared_ptr< Geometry > > geometries;

	b2World world;										// Referencia al mundo

	float physics_to_graphics_scale = 10.f;			// Escala de físicas según la escala

	RenderWindow* window;								// La referencia a la window donde se van a  dibujar los objetos

	const float target_fps = 60.f;                      // Cuántos fotogramas por segundo se busca conseguir
	const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

	float delta_time = target_time;                     // Previsión de la duración del fotograma actual

	ContactListener contact_listener;

	Clock timer;

	float left = 0.01f;
	float right = 8.00f;
	float top = 6.00f;
	float bottom = 0.01f;

	bool  exit = false;

	/// <summary>
	/// Variable para el movimiento en x del jugador
	/// </summary>
	int move_x = 0;
	/// <summary>
	/// Variable para el movimiento en y del jugador
	/// </summary>
	int move_y = 0;

public:

	/// <summary>
	/// Constructor de escena
	/// </summary>
	/// <param name="given_window"></param>
	Scene(const RenderWindow& given_window) : world(b2Vec2(0.0f, -10.0f))
	{
		window = const_cast<RenderWindow*>(&given_window);
		world.SetContactListener(&contact_listener);
		create_scene();
	}

	/// <summary>
	/// Getter de World
	/// </summary>
	/// <returns></returns>
	b2World & get_world()
	{
		return world;
	}

	/// <summary>
	/// Obtiene el mapa de gemotries
	/// </summary>
	/// <returns></returns>
	map < string, shared_ptr< Geometry > > get_geometries() 
	{
		return geometries;
	}

	/// <summary>
	/// Getter de escala de gráficos a la escena
	/// </summary>
	/// <returns></returns>
	const float get_physics_to_graphics_scale() 
	{
		return physics_to_graphics_scale;
	}

	/// <summary>
	/// Conversor de posiciones
	/// </summary>
	/// <param name="box2d_position"></param>
	/// <returns></returns>
	Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position)
	{
		return Vector2f(box2d_position.x * physics_to_graphics_scale, window->getSize().y - box2d_position.y * physics_to_graphics_scale);
	}

	/// <summary>
	/// Bucle principal donde se procesa la escena
	/// </summary>
	void run()
	{
		exit = false;

		create_scene();

		do
		{
			process_events();

			world.Step(1.f / 60.f, 4, 4);

			update();

			window->clear();

			render();

			window->display();

		} while (!exit);
	}

	/// <summary>
	/// Se pasa por todas las geometries y se ejecuta el método update
	/// </summary>
	void update();

private:

	/// <summary>
	/// Activa el método render de todos los objetos de padre geometry
	/// </summary>
	void render();

	/// <summary>
	/// Acciona todo el método create de los elementos del map de Geometries
	/// </summary>
	void create_scene();		

	/// <summary>
	/// Procesa el ciclo de la escena y los eventos de teclado
	/// </summary>
	void process_events();

	/// <summary>
	/// Se acciona el método reset_position() de todas las geometries
	/// </summary>
	void reset_scene();
};