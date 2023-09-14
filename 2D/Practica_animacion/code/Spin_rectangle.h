/**
* @file Spin_rectangle.h
* @brief Hija de Geometry, se encarga de crear rectangulos con angulaci�n en la escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear rectangulos con angulaci�n en la escena
/// </summary>
class Spin_Rectangle : public Geometry
{
	float width;
	float height;
	float rotation = 0;

	Color color;

public:

	/// <summary>
	/// Constructor del objeto Spin_Rectangle
	/// </summary>
	/// <param name="given_width"></param>
	/// <param name="given_height"></param>
	/// <param name="given_scene"></param>
	Spin_Rectangle(float given_width, float given_height, Scene* given_scene) : Geometry(*given_scene)
	{
		width = given_width;
		height = given_height;
	}

	/// <summary>
	/// Se configura la rotaci�n del objeto
	/// </summary>
	/// <param name="rotation"></param>
	void set_rotation(float rotation)
	{
		b2Vec2 position = body->GetPosition();
		body->SetTransform(position, rotation * b2_pi / 180.0f);
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, float new_rotation, Scene* scene)
	{
		shared_ptr< Spin_Rectangle > rectangle(new Spin_Rectangle(width, height, scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y);                            // Posici�n inicial absoluta
		body_def.angle = new_rotation;

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

		rectangle->body->CreateFixture(&body_fixture);

		rectangle->shape = make_unique<sf::RectangleShape>(Vector2f(width * scene->get_physics_to_graphics_scale(), height * scene->get_physics_to_graphics_scale()));

		rectangle->initial_position = { x, y };

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(rectangle.get());

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
		return "Spin_rectangle_geo";
	}

	/// <summary>
	/// Resetteas la posici�n
	/// </summary>
	void reset_position()
	{
		// Establecer la nueva posici�n del cuerpo r�gido
		body->SetTransform(initial_position, 0.0f);
	}

	/// <summary>
	/// Metodo de render
	/// </summary>
	/// <param name="renderer"></param>
	void render(RenderWindow& renderer) override
	{
		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		// Aplicar la rotaci�n al objeto
		rectangle->setRotation(body->GetAngle() * 180.0f / b2_pi);

		rectangle->setFillColor(Color::Blue);

		renderer.draw(*rectangle);
	}
};
