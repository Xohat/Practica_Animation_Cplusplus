//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
//

#pragma once

#include "Geometry.h"

class Segment : public Geometry 
{

public:

	b2Body* create (b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1)
	{
		// Se crea el body:

		b2BodyDef body_definition;

		body_definition.type = body_type;
		body_definition.position.Set(0.f, 0.f);                        // Posición inicial absoluta

		b2Body* body = physics_world.CreateBody(&body_definition);

		// Se añande una fixture:

		b2EdgeShape body_shape;

		body_shape.SetTwoSided(b2Vec2(x0, y0), b2Vec2(x1, y1));        // Coordenadas locales respecto al centro del body

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;

		body->CreateFixture(&body_fixture);

		return body;
	}

	void render_segment
	(
		b2Vec2              start,
		b2Vec2              end,
		const b2Transform& transform,
		RenderWindow& renderer,
		float               window_height,
		float               scale
	)
	{
		start = b2Mul(transform, start);
		end = b2Mul(transform, end);

		render_segment
		(
			adapter.box2d_position_to_sfml_position(start, window_height, scale),
			adapter.box2d_position_to_sfml_position(end, window_height, scale),
			Color::Green,
			renderer
		);
	}

	void render_segment
	(
		const Vector2f& start,
		const Vector2f& end,
		const Color& color,
		RenderWindow& renderer
	)
	{
		Vertex line[] =
		{
			Vertex(start, color),
			Vertex(end, color),
		};

		renderer.draw(line, 2, Lines);
	}
};