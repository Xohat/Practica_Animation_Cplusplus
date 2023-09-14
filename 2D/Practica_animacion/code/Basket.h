/**
* @file Basket.h
* @brief Hija de Geometry, se encarga de crear el basket de 45 grados en la escena
* Un basket son basicamente dos spin_rectangles con una diferencia de 45 grados entre ellos
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Geometry.h"

/// <summary>
/// Hija de Geometry, se encarga de crear el basket de 45 grados en la escena
/// Un basket son basicamente dos spin_rectangles con una diferencia de 45 grados entre ellos
/// </summary>
class Basket : public Geometry
{
	float width;
	float height;

	float basket_angle = 45.f;

public:

	//KINEMATIC
	Basket(float given_width, float given_height, Scene* given_scene) : Geometry(*given_scene)
	{
		width = given_width;
		height = given_height;
	}

	/// <summary>
	/// Se configura la rotaci�n de lso rect�ngulos
	/// </summary>
	/// <param name="rotation"></param>
	void setRotation(float rotation)
	{
		body->SetTransform(body->GetPosition(), rotation);
	}

	/// <summary>
	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
	/// </summary>
	/// <param name="body_type"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, float new_rotation, Scene* scene)
	{
		shared_ptr< Basket > basket(new Basket(width, height, scene));

		// Se crea el body def:
		b2BodyDef body_def;

		body_def.type = body_type;
		body_def.position.Set(x, y); // Posici�n inicial absoluta
		body_def.angle = new_rotation;

		// Se crea el body:

		basket->body = basket->scene->get_world().CreateBody(&body_def);

		// Se a�ande una shape:

		b2PolygonShape body_shape;

		body_shape.SetAsBox(width, height);

		// Se a�ande una fixture:

		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.50f;
		body_fixture.friction = 0.50f;

		basket->body->CreateFixture(&body_fixture);

		basket->shape = make_unique<sf::RectangleShape>(Vector2f(width * scene->get_physics_to_graphics_scale(), height * scene->get_physics_to_graphics_scale()));

		uintptr_t entityPtr = reinterpret_cast<uintptr_t>(basket.get());

		return basket;
	}

	/// <summary>
	/// M�todo update en caso de necesitarlo por alguna raz�n
	/// </summary>
	void update()
	{

	}

	/// <summary>
	/// Obtienes el tipo de la geometria
	/// </summary>
	/// <returns></returns>
	std::string get_type() const
	{
		return "Basket_geo";
	}

	/// <summary>
	/// Resetteas la posici�n
	/// </summary>
	void reset_position() 
	{
		// Establecer la nueva posici�n del cuerpo r�gido
		body->SetTransform(initial_position, 0.0f);
	}

	/// <summary>
	/// Renderizas el objeto, m�todo override ya que se define en Geometry.h
	/// </summary>
	/// <param name="renderer"></param>
	void render(RenderWindow& renderer) override
	{

		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		// Aplicar la rotaci�n al objeto
		rectangle->setRotation(body->GetAngle() * 180.0f / b2_pi);

		rectangle->setFillColor(Color::Red);

		renderer.draw(*rectangle);
	}
};