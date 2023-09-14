/**
* @file Geometry.h
* @brief Clase encargada de proporcionar los datos a todos sus hijos que son todas las formas geométricas de la escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Scene.h"
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/// <summary>
/// Clase encargada de proporcionar los datos a todos sus hijos que son todas las formas geométricas de la escena
/// </summary>
class Geometry
{

protected:

	// Aquí está el transform que hay que usar

	unique_ptr< sf::Shape > shape;

	Scene* scene;

	b2Vec2 initial_position;

public:

	b2Body* body = nullptr;

	bool damage = false;
	bool triggered = false;
	bool player = false;
	bool dead = false;

	/// <summary>
	/// Lo unico que necesita Geometry es una escena para que luego los objetos puedan pintarse correctamente
	/// </summary>
	/// <param name="given_scene"></param>
	Geometry(Scene& given_scene)
	{ 
		scene = &given_scene; 
	}

	/// <summary>
	/// Metodo virtual de render para todos los hijos
	/// </summary>
	/// <param name="renderer"></param>
	virtual void render(RenderWindow& renderer) = 0;

	/// <summary>
	/// Método virtual update en caso de necesitarlo por alguna razón
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	virtual std::string get_type() const = 0;

	/// <summary>
	/// Resettea la posición de los elementos a su posición inicial guardada en la construcción de los mismos
	/// </summary>
	void reset_position()
	{
		// Establecer la nueva posición del cuerpo rígido
		body->SetTransform(initial_position, 0.0f);
	}

	/// <summary>
	/// Configura cual es el body de box2D
	/// </summary>
	/// <param name="new_body"></param>
	void set_body(b2Body* new_body)
	{
		body = new_body;
	}

	/// <summary>
	/// Getter de body de box2D
	/// </summary>
	/// <returns></returns>
	b2Body* get_body() 
	{
		return body;
	}

	/// <summary>
	/// Getter de position
	/// </summary>
	/// <returns></returns>
	b2Vec2 get_position()
	{
		return body->GetTransform().p;
	}

	/// <summary>
	/// Setter de position sin angulo
	/// </summary>
	/// <param name="new_position"></param>
	void set_position(b2Vec2 new_position)
	{
		body->SetTransform(new_position, 0.f);
	}

	/// <summary>
	/// Setter de position con angulo
	/// </summary>
	/// <param name="new_position"></param>
	/// <param name="angle"></param>
	void set_position(b2Vec2 new_position, float angle)
	{
		body->SetTransform(new_position, angle);
	}
};
