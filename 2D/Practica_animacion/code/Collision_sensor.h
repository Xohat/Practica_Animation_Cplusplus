/**
* @file Collision_sensor.h
* @brief Hija de Geometry, crea un rect�ngulo pero carece de colisiones f�sicas, solo act�a comno un sensor
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#//include "Geometry.h"
#include "Rectangle_platform.h"
#include <chrono>
#include <thread>

/// <summary>
/// Hija de Geometry, crea un rect�ngulo pero carece de colisiones f�sicas, solo act�a comno un sensor
/// </summary>
class Collision_Sensor : public Geometry
{
	float width;
	float height;

	Rectangle_Platform* platform_to_move;

public:

	/// <summary>
	/// Constructor de Collision Sensor
	/// </summary>
	/// <param name="given_width"></param>
	/// <param name="given_height"></param>
	/// <param name="given_scene"></param>
	Collision_Sensor(float given_width, float given_height, Scene* given_scene) : Geometry(*given_scene)
	{
		width = given_width;
		height = given_height;
	}

	/// <summary>
	/// Configura cual es la plataforma hija para luego al hacer la colisi�n poder cambiarle la variable de triggered
	/// </summary>
	/// <param name="new_platform"></param>
	void set_platform(Rectangle_Platform* new_platform)
	{
		platform_to_move = new_platform;
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, Scene* scene)
	{
		shared_ptr< Collision_Sensor > rectangle(new Collision_Sensor(width, height, scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y);                            // Posici�n inicial absoluta

		// Se crea el body:

		rectangle->body = rectangle->scene->get_world().CreateBody(&body_def);

		// Se a�ande una shape:

		b2PolygonShape body_shape;

		body_shape.SetAsBox(width, 0);

		// Se a�ande una fixture:

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.50f;
		body_fixture.friction = 0.50f;

		body_fixture.isSensor = true;

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(rectangle.get());
		body_fixture.userData.pointer = entityPtr;

		//b2FixtureUserData fixtureUserData;
		//fixtureUserData.pointer = reinterpret_cast<uintptr_t>(new std::string("up_platform"));
		//body_fixture.userData = fixtureUserData;

		rectangle->body->CreateFixture(&body_fixture);

		rectangle->shape = make_unique<sf::RectangleShape>(Vector2f(width * scene->get_physics_to_graphics_scale(), height * scene->get_physics_to_graphics_scale()));

		rectangle->initial_position = { x , y };

		return rectangle;
	}

	/// <summary>
	/// M�todo update en caso de necesitarlo por alguna raz�n
	/// </summary>
	void update()
	{

	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	std::string get_type() const
	{
		return "Collision_sensor_geo";
	}

	/// <summary>
	/// Renderizas el objeto, m�todo override ya que se define en Geometry.h
	/// </summary>
	/// <param name="renderer"></param>
	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplic�rselo a shape ajust�ndolo para SFML
		// dibujar shape

		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		rectangle->setFillColor(Color::Red);

		renderer.draw(*rectangle);
	}
};