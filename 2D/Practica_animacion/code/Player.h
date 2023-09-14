/**
* @file Player.h
* @brief Clase encargada del jugador, que en este caso es la bola debido a problemas con Box2D
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Circle.h"
#include "Geometry.h"

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/// <summary>
/// Clase encargada del jugador, que en este caso es la bola debido a problemas con Box2D
/// </summary>
/// <param name="player"></param>
class Player : public Geometry
{
	shared_ptr< Geometry > player_body;
	b2Vec2 initial_position;

public:

	Player(Scene* given_scene) : Geometry (*given_scene)
	{
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float radius, float density, Scene* scene)
	{
		shared_ptr< Player > circle(new Player(scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y);                            // Posición inicial absoluta

		// Se crea el body:

		circle->body = circle->scene->get_world().CreateBody(&body_def);

		// Se añande una shape:

		b2CircleShape body_shape;

		body_shape.m_radius = radius;

		// Se añande una fixture:

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 0.10f;
		body_fixture.restitution = 0.0f;
		body_fixture.friction = 0.50f;

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(circle.get());

		body_fixture.userData.pointer = entityPtr;

		circle->body->CreateFixture(&body_fixture);

		circle->shape = make_unique<sf::CircleShape>(radius * scene->get_physics_to_graphics_scale());

		circle->initial_position = { x , y };

		return circle;
	}

	/// <summary>
	/// Se configura el body del player
	/// </summary>
	/// <param name="new_player_body"></param>
	void set_player_body(shared_ptr< Geometry > new_player_body)
	{
		player_body = new_player_body;
	}

	/// <summary>
	/// Método update en caso de necesitarlo por alguna razón
	/// </summary>
	void update()
	{
		
	}


	/// <summary>
	/// Metodo de render
	/// </summary>
	/// <param name="renderer"></param>
	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplicárselo a shape ajustándolo para SFML
		// dibujar shape

		b2CircleShape* body_circle = dynamic_cast<b2CircleShape*>(body->GetFixtureList()->GetShape());

		float radius = body_circle->m_radius * scene->get_physics_to_graphics_scale();
		auto  center = body_circle->m_p;

		sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		circle->setPosition(scene->box2d_position_to_sfml_position(b2Mul(body_transform, center))
			- Vector2f(radius, radius));

		circle->setFillColor(Color::Cyan);

		renderer.draw(*circle);
	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	std::string get_type() const
	{
		return "Player_geo";
	}

	/// <summary>
	/// Setter de posición
	/// </summary>
	/// <param name="new_position"></param>
	void set_position(b2Vec2 new_position) 
	{
		body->SetTransform(new_position, 0.0f);
	}

	/// <summary>
	/// Getter del body de box2D de player
	/// </summary>
	/// <returns></returns>
	shared_ptr< Geometry > get_player_body()
	{
		return player_body;
	}
};