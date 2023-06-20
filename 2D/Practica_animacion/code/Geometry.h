// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include "Scene.h"
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/// <summary>
/// Clase encargada de proporcionar los datos a todos sus hijos que son todas las formas geométricas
/// </summary>
class Geometry
{

protected:

	b2Body* body = nullptr;							// Aquí está el transform que hay que usar

	unique_ptr< sf::Shape > shape;

	int name_offset = 0;

	Scene* scene;

public:

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
