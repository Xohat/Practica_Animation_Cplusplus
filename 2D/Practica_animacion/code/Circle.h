#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Circle 
{


public:

	Circle() 
	{

	}

	b2Body* create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius)
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
};