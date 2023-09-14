/**
* @file Circle.h
* @brief Hija de Geometry, se encarga de crear circulos en la escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear circulos en la escena
/// </summary>
class Circle : public Geometry
{
	b2Vec2 initial_position;

private:

	//KINEMATIC
	Circle(Scene *given_scene) : Geometry(*given_scene)
	{
	}

public:

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float radius, float density, Scene *scene)
	{
		shared_ptr< Circle > circle(new Circle (scene));

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

		circle->body->CreateFixture(&body_fixture);

		circle->shape = make_unique<sf::CircleShape>(radius * scene->get_physics_to_graphics_scale());

		circle->initial_position = { x , y };

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(circle.get());

		return circle;
	}

	/// <summary>
	/// Método update en caso de necesitarlo por alguna razón
	/// </summary>
	void update()
	{

	}

	/// <summary>
	/// Resetteas la posición
	/// </summary>
	std::string get_type() const
	{
		return "Circle_geo";
	}

	/// <summary>
	/// Renderizas el objeto, método override ya que se define en Geometry.h
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

		circle->setFillColor(Color::Magenta);

		renderer.draw(*circle);		
	}
};