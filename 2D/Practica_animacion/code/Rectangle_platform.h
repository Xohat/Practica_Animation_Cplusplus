/**
* @file Rectangle_platform.h
* @brief Hija de Geometry, se encarga de crear plataformas rectangulares en la escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04


#pragma once

#include "Geometry.h"
#include <chrono>
#include <thread>

/// <summary>
/// Hija de Geometry, se encarga de crear plataformas rectangulares en la escena
/// </summary>
class Rectangle_Platform : public Geometry
{
	float width;
	float height;

	float final_y_position;

	bool triggered = false;

	float time = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) / 1000.0f;

public:

	//STATIC
	Rectangle_Platform(float given_width, float given_height, Scene* given_scene) : Geometry(*given_scene)
	{
		width = given_width;
		height = given_height;
	}

	/// <summary>
	/// Acciona el movimiento por el update_movement()
	/// </summary>
	void set_triggered() 
	{
		triggered = true;
	}

	/// <summary>
	/// Obtiene la posición del body de box2D
	/// </summary>
	/// <returns></returns>
	b2Vec2 get_position() 
	{
		return body->GetPosition();
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, float y_upping, Scene* scene)
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
		rectangle->final_y_position = y_upping;

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(rectangle.get());

		return rectangle;
	}

	/// <summary>
	/// Obtienes el tiempo que lleva la plataforma parada
	/// </summary>
	/// <returns></returns>
	float get_time() 
	{
		return time;
	}

	/// <summary>
	/// Método update para actualizar el tiempo que la plataforma esta parada para su descenso posterior
	/// </summary>
	void update() 
	{
		time += 0.0016f;
	}

	/// <summary>
	/// Obtienes la y final del objeto, donde va a llegar a su máximo
	/// </summary>
	/// <returns></returns>
	float get_final_y() 
	{
		return final_y_position;
	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	std::string get_type() const
	{
		return "Rectangle_platform_geo";
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

		rectangle->setFillColor(Color::Green);

		renderer.draw(*rectangle);
	}

	/// <summary>
	/// Se encarga de mover la plataforma hasta la posición en y definida por código
	/// </summary>
	/// <param name="renderer"></param>
	void update_movement(float delta_time)
	{
		if (triggered) 
		{
			b2Body* body = this->get_body();

			if (body->GetPosition().y < 40.f)
			{
				body->SetTransform(body->GetPosition() + b2Vec2(0, 8. / 60), body->GetAngle());
				time = 0;
			}
			else
			{
				body->SetTransform(body->GetPosition() - b2Vec2(0, 8. / 60), body->GetAngle());
				time = 0;
			}
		}		
	}

	/// <summary>
	/// Se encarga de mover la plataforma desde la posición y definida hasta la initialPosition
	/// </summary>
	/// <param name="renderer"></param>
	void reset_movement(float delta_time)
	{
		b2Body* body = this->get_body();

		if (body->GetPosition().y >= 40.f && time >= 5.f)
		{
			body->SetTransform(body->GetPosition() - b2Vec2(0, 8. / 60), body->GetAngle());
		}
	}
};


