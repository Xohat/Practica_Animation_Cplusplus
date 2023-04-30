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

#include "Scene.h"
#include <ciso646>
#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Geometry
{
protected:

	b2Body* body;					// Aquí está el transform que hay que usar
	unique_ptr< sf::Shape > shape;

	Scene* scene;

public:

	Geometry(Scene& given_scene) { scene = &given_scene; }

	virtual void render(RenderWindow& renderer) = 0;

};


class Circle : public Geometry
{

public:

	Circle(Scene& given_scene, float radius, float density, ...) : Geometry(scene) { }

	void render(RenderWindow& renderer) override
	{
		// coger el transform de body
		// aplicárselo a shape ajustándolo para SFML
		// dibujar shape

		b2CircleShape* body_circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

		auto center = body_circle->m_p;

		sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(shape.get());

		const b2Transform& body_transform = body->GetTransform();

		circle->setPosition(scene->box2d_position_to_sfml_position(b2Mul(body_transform, center))
			- Vector2f(radius, radius));

		renderer.draw(*circle);
	}

};