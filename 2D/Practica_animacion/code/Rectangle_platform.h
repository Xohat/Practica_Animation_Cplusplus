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

class Rectangle_Platform : public Geometry
{
	float width;
	float height;

public:

	//KINEMATIC
	Rectangle_Platform(float given_width, float given_height) : Geometry(*scene)
	{
		width = given_width;
		height = given_height;
	}

	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplicárselo a shape ajustándolo para SFML
		// dibujar shape

		b2PolygonShape* body_circle = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());

		sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		rectangle->setPosition(scene->box2d_position_to_sfml_position(body_transform.p));

		rectangle->setFillColor(Color::Green);

		renderer.draw(*rectangle);
	}

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

	void detect_collisions()
	{
		b2PolygonShape shape;
		shape.SetAsBox(width / 2.0f, height / 2.0f); // Crea la forma rectangular

		b2FixtureDef fixture_def;
		fixture_def.shape = &shape;
		fixture_def.friction = 0.0f; // Establece el coeficiente de fricción en 0 para que la plataforma no se deslice

		body->CreateFixture(&fixture_def); // Añade la fixture al cuerpo de la plataforma
	}
};

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) 
	{
		// Obtén los fixtures involucrados en la colisión
		b2Fixture* fixture_a = contact->GetFixtureA();
		b2Fixture* fixture_b = contact->GetFixtureB();

		// Comprueba si la colisión es entre la plataforma y el jugador
		if (fixture_a->GetUserData() == "platform" && fixture_b->GetUserData() == "player") {
			// Si la plataforma está colisionando con el jugador, haz que se mueva hacia arriba
			Rectangle_Platform* platform = static_cast<Rectangle_Platform*>(fixture_a->GetBody()->GetUserData());
			platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
		}
	}
};
