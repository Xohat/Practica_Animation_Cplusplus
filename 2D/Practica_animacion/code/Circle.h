//
// Este código es de dominio público.
// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear circulos en la escena
/// </summary>
class Circle : public Geometry
{

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
		body_fixture.restitution = 0.75f;
		body_fixture.friction = 0.50f;
		//body_fixture.isSensor = true;

		//std::string userData_name = "player";
		//circle->body_fixture.userData = userData_name.c_str();

		circle->body->CreateFixture(&body_fixture);

		circle->shape = make_unique<sf::CircleShape>(radius * scene->get_physics_to_graphics_scale());

		return circle;
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

		circle->setFillColor(Color::Magenta);

		renderer.draw(*circle);		
	}
};