// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear plataformas rectangulares en la escena
/// </summary>
class Rectangle_Platform : public Geometry
{
	float width;
	float height;

public:

	//STATIC
	Rectangle_Platform(float given_width, float given_height, Scene* given_scene) : Geometry(*given_scene)
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
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, Scene* scene)
	{
		shared_ptr< Rectangle_Platform > rectangle(new Rectangle_Platform(width, height, scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y);                            // Posición inicial absoluta

		// Se crea el body:

		rectangle->body = rectangle->scene->get_world().CreateBody(&body_def);

		// Se añande una shape:

		b2PolygonShape body_shape;

		body_shape.SetAsBox(width, height);

		// Se añande una fixture:

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.50f;
		body_fixture.friction = 0.50f;
		body_fixture.isSensor = true;

		b2FixtureUserData fixtureUserData;
		fixtureUserData.pointer = reinterpret_cast<uintptr_t>(new std::string("up_platform"));
		body_fixture.userData = fixtureUserData;

		rectangle->body->CreateFixture(&body_fixture);

		rectangle->shape = make_unique<sf::RectangleShape>(Vector2f(width * scene->get_physics_to_graphics_scale(), height * scene->get_physics_to_graphics_scale()));

		return rectangle;
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

		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		rectangle->setFillColor(Color::Blue);

		renderer.draw(*rectangle);
	}

	/// <summary>
	/// Se encarga de mover la plataforma
	/// </summary>
	/// <param name="renderer"></param>
	void update_movement(float time_step)
	{
		// Obtener la posición actual del cuerpo rígido
		const b2Vec2& current_pos = body->GetPosition();

		// Calcular la nueva posición en función del tiempo transcurrido y de la velocidad deseada
		float speed = 2.0f; // velocidad en unidades por segundo
		float distance = 2.0f; // distancia en unidades que se moverá hacia arriba y hacia abajo

		b2Vec2 new_pos = current_pos + b2Vec2(0.0f, distance * sin(speed * 2.0f * b2_pi * time_step))
			- b2Mul(body->GetTransform().q, b2Vec2(0.0f, height / 2.0f));

		// Establecer la nueva posición del cuerpo rígido
		body->SetTransform(new_pos, 0.0f);
	}
};


