// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

	Clock timer;

	float left = 0.01f;
	float right = 8.00f;
	float top = 6.00f;
	float bottom = 0.01f;

	bool  exit = false;

public:

	//Constructor de Scene
	Scene(const RenderWindow& given_window) : world(b2Vec2(0.0f, -10.0f))
	{
		window = const_cast<RenderWindow*>(&given_window);
		create_scene();
	}

	//Getter de world
	b2World & get_world()
	{
		return world;
	}

	const float get_physics_to_graphics_scale() 
	{
		return physics_to_graphics_scale;
	}

	//Conversor de posiciones
	Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position)
	{
		return Vector2f(box2d_position.x * physics_to_graphics_scale, window->getSize().y - box2d_position.y * physics_to_graphics_scale);
	}

	//Bucle principal donde se procesa la escena
	void run()
	{
		exit = false;

		create_scene();

		do
		{
			process_events();

			world.Step(1.f / 60.f, 4, 4);

			window->clear();

			render();

			window->display();

		} while (!exit);
	}


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

};