//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
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

class Circle : public Geometry
{
	float radius;
	float density;

public:

	Circle(float given_radius, float given_density) : Geometry(*scene)	
	{
		radius = given_radius;
		density = given_density;
	}

	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplicárselo a shape ajustándolo para SFML
		// dibujar shape

		b2CircleShape* body_circle = dynamic_cast<b2CircleShape*>(body->GetFixtureList()->GetShape());

		auto center = body_circle->m_p;

		sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		circle->setPosition(scene->box2d_position_to_sfml_position(b2Mul(body_transform, center))
			- Vector2f(radius, radius));

		renderer.draw(*circle);
	}

};

/*
	class Circle : public Geometry 
	{


		Circle(Scene & scene, float radius, float density, float friction) : Geometry(scene)
		{
			// b2BodyDef body_definition;
			// ...
			// body = scene.get_world ().CreateBody (body_definition);
			// Añadir una fixture de tipo círculo.
			// shape = make_unique< sf::CircleShape >(radius * scene.get_scale());
		}

		/*

		float radius;

	public:

		Circle (Adapter given_adapter, b2World given_world, b2BodyDef given_body_definition ,float given_x, float given_y, float given_radius)
		{
			adapter = given_adapter;
			physics_world = given_world;
			body_type = given_body_definition.type;
			x = given_x;
			y = given_y;
			radius = given_radius;
		}

		b2Body* create ()
		{
			// Se crea el body:

			b2BodyDef body_definition;

			body_definition.type = body_type;
			body_definition.position.Set(x, y);                            // Posición inicial absoluta

			b2Body* body = physics_world.CreateBody(&body_definition);

			// Se añande una fixture:

			b2CircleShape body_shape;

			body_shape.m_radius = radius;

			b2FixtureDef body_fixture;

			body_fixture.shape = &body_shape;
			body_fixture.density = 0.10f;
			body_fixture.restitution = 0.75f;
			body_fixture.friction = 0.50f;

			body->CreateFixture(&body_fixture);

			return body;
		}

		void render (const b2Vec2* vertices, int number_of_vertices, const b2Transform& transform,
							RenderWindow& renderer, float window_height, float scale, Color	color)
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