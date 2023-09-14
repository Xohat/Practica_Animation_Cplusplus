/**
* @file Rectangle.h
* @brief Hija de Geometry, se encarga de crear rectángulos
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear rectángulos
/// </summary>
class Rectangle : public Geometry
{
	float width;
	float height;
	Color color;

public:

	//STATIC
	Rectangle(float given_width, float given_height, Scene *given_scene) : Geometry(*given_scene)
	{
		width = given_width;
		height = given_height;
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, Scene *scene)
	{
		shared_ptr< Rectangle > rectangle(new Rectangle(width, height, scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y);                            // Posición inicial absoluta

		// Se crea el body:

		rectangle->body = rectangle->scene->get_world().CreateBody(&body_def);

		// Se añande una shape:

		b2PolygonShape body_shape;

		body_shape.SetAsBox(width, 0);

		// Se añande una fixture:

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.50f;
		body_fixture.friction = 0.50f;

		rectangle->body->CreateFixture(&body_fixture);

		rectangle->shape = make_unique<sf::RectangleShape>(Vector2f(width * scene->get_physics_to_graphics_scale(), height * scene->get_physics_to_graphics_scale()));

		rectangle->initial_position = { x , y };

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(rectangle.get());

		return rectangle;
	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	void update()
	{

	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	std::string get_type() const
	{
		return "Rectangle_geo";
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

		rectangle->setFillColor(Color::Blue);

		renderer.draw(*rectangle);
	}
};
