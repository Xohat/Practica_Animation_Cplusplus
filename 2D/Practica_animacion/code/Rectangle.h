//// Copyright (C) 2023
//// Hecho por Arturo Vilar Carretero
//// 2023.4+
//
//#pragma once
//
//#include "Geometry.h"
//
///// <summary>
///// Hija de Geometry, se encarga de crear rectangulos en la escena
///// </summary>
//class Rectangle : public Geometry
//{
//	float width;
//	float height;
//
//public:
//
//	//STATIC
//	Rectangle(float given_width, float given_height, Scene *given_scene) : Geometry(*scene)
//	{
//		width = given_width;
//		height = given_height;
//	}
//
//	/// <summary>
//	/// Se crea el objeto y se devuelve la referencia para meterlo en el mapa de escena despues
//	/// </summary>
//	/// <param name="body_type"></param>
//	/// <param name="x"></param>
//	/// <param name="y"></param>
//	/// <returns></returns>
//	static shared_ptr< Geometry > create(b2BodyType body_type, float x, float y, float width, float height, Scene *scene)
//	{
//		auto rectangle = make_shared< Rectangle >(width, height, scene);
//
//		// Se crea el body def:
//		b2BodyDef body_def;
//
//		// Se crea el body:
//
//		body_def->type = body_type;
//		body_def->position.Set(0.f, 0.f);                           // Posición inicial absoluta
//
//		b2Body* body = scene->get_world().CreateBody(body_def);
//
//		// Se añande una fixture:
//
//		b2PolygonShape body_shape;
//
//		body_shape.SetAsBox(width, height);
//
//		b2FixtureDef body_fixture;
//
//		body_fixture.shape = &body_shape;
//		body_fixture.density = 1.00f;
//		body_fixture.restitution = 0.50f;
//		body_fixture.friction = 0.50f;
//
//		body->CreateFixture(&body_fixture);
//
//		rectangle->shape = make_unique<sf::RectangleShape>(width * scene->get_physics_to_graphics_scale());
//
//		return rectangle;
//	}
//
//	/// <summary>
//	/// Metodo de render
//	/// </summary>
//	/// <param name="renderer"></param>
//	void render(RenderWindow& renderer) override
//	{
//		// coger el transform de body
//		// aplicárselo a shape ajustándolo para SFML
//		// dibujar shape
//
//		b2PolygonShape* body_rectangle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
//
//		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());
//
//		const b2Transform& body_transform = body->GetTransform();
//
//		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));
//
//		rectangle->setFillColor(Color::Blue);
//
//		renderer.draw(*rectangle);
//	}
//};
