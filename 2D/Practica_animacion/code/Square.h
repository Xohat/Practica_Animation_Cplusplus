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

/*
	class Square : public Geometry 
	{
		float width;
		float height;

	public:

		Square (Adapter given_adapter, b2World given_world, b2BodyDef given_body_definition, float given_x, float given_y, float given_width, float given_height)
		{
			adapter = given_adapter;
			physics_world = given_world;
			body_type = given_body_definition.type;
			x = given_x;
			y = given_y;
			radius = given_radius;
		}

		b2Body* create (b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
		{
			// Se crea el body:

			b2BodyDef body_definition;

			body_definition.type = body_type;
			body_definition.position.Set(x, y);                            // Posición inicial absoluta

			b2Body* body = physics_world.CreateBody(&body_definition);

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

		void render_polygon	( const b2Vec2* vertices, int number_of_vertices, const b2Transform& transform,
							  RenderWindow& renderer, float window_height, float scale, Color color )
		{
			ConvexShape sfml_polygon;

			sfml_polygon.setPointCount(number_of_vertices);
			sfml_polygon.setFillColor(color);

			for (int index = 0; index < number_of_vertices; index++)
			{
				sfml_polygon.setPoint
				(
					index,
					adapter.box2d_position_to_sfml_position(b2Mul(transform, vertices[index]), window_height, scale)
				);
			}

			renderer.draw(sfml_polygon);
		}
	};
*/
