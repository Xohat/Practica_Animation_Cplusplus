//// Copyright (C) 2023
//// Hecho por Arturo Vilar Carretero
//// 2023.4+
//
//#pragma once
//
//#include "Geometry.h"
//
///// <summary>
///// Hija de Geometry, se encarga de crear plataformas rectangulares en la escena
///// </summary>
//class Rectangle_Platform : public Geometry
//{
//	ContactListener listener;
//
//	float width;
//	float height;
//
//public:
//
//	//KINEMATIC
//	Rectangle_Platform(float given_width, float given_height) : Geometry(*scene)
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
//
//	b2Body* create(b2BodyType body_type, float x, float y)
//	{
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
//		std::string userData_name = "platform";
//		body_fixture.userData = userData_name.c_str();
//
//		body->CreateFixture(&body_fixture);
//
//		return body;
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
//		b2PolygonShape* body_circle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
//
//		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());
//
//		const b2Transform& body_transform = body->GetTransform();
//
//		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));
//
//		rectangle->setFillColor(Color::Green);
//
//		renderer.draw(*rectangle);
//	}
//
//	/// <summary>
//	/// Se encarga de mover la plataforma
//	/// </summary>
//	/// <param name="renderer"></param>
//	void update_movement(float time_step)
//	{
//		// Obtener la posición actual del cuerpo rígido
//		const b2Vec2& current_pos = body->GetPosition();
//
//		// Calcular la nueva posición en función del tiempo transcurrido y de la velocidad deseada
//		float speed = 2.0f; // velocidad en unidades por segundo
//		float distance = 2.0f; // distancia en unidades que se moverá hacia arriba y hacia abajo
//
//		b2Vec2 new_pos = current_pos + b2Vec2(0.0f, distance * sin(speed * 2.0f * b2_pi * time_step))
//			- b2Mul(body->GetTransform().q, b2Vec2(0.0f, height / 2.0f));
//
//		// Establecer la nueva posición del cuerpo rígido
//		body->SetTransform(new_pos, 0.0f);
//	}
//};
//
///// <summary>
///// Detector de colisiones
///// </summary>
///// <param name="contact"></param>
//class ContactListener : public b2ContactListener
//{
//	/// <summary>
//	/// Detecta la colisión en base al user data proporcionado en el create de las dos partes
//	/// </summary>
//	/// <param name="contact"></param>
//	void BeginContact(b2Contact* contact) 
//	{
//		// Obtén los fixtures involucrados en la colisión
//		b2Fixture* fixture_a = contact->GetFixtureA();
//		b2Fixture* fixture_b = contact->GetFixtureB();
//
//		fixture_a->GetUserData();
//
//		// Comprueba si la colisión es entre la plataforma y el jugador
//		if (fixture_a->GetUserData() == "platform" && fixture_b->GetUserData() == "player") 
//		{
//			// Si la plataforma está colisionando con el jugador, haz que se mueva hacia arriba
//			Rectangle_Platform* platform = static_cast<Rectangle_Platform*>(fixture_a->GetBody()->GetUserData());
//			platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
//		}
//	}
//};
