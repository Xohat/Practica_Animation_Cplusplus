// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear el basket de 45 grados en la escena
/// </summary>
class Basket : public Geometry 
{
	float width;
	float height;

public:

	//KINEMATIC
	Basket(float given_width, float given_height) : Geometry(*scene)
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
	b2Body* create(b2BodyType body_type, float x, float y)
	{
		// Se crea el body:

		body_def->type = body_type;
		body_def->angle = 45.f;
		body_def->position.Set(0.f, 0.f);                           // Posición inicial absoluta

		b2Body* body = scene->get_world().CreateBody(body_def);

		// Se añande una fixture:

		b2PolygonShape body_shape;

		body_shape.SetAsBox(width, height);

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.50f;
		body_fixture.friction = 0.50f;

		body->CreateFixture(&body_fixture);

		return body;
	}

	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplicárselo a shape ajustándolo para SFML
		// dibujar shape

		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		rectangle->setFillColor(Color::Red);

		renderer.draw(*rectangle);
	}
};
