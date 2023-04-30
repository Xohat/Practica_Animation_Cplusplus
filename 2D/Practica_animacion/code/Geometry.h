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

using namespace sf;
using namespace std;

class Geometry
{
protected:

	b2Body* body = 0;					// Aquí está el transform que hay que usar
	unique_ptr< sf::Shape > shape;

	Scene* scene;

public:

	Geometry(Scene& given_scene) 
	{ 
		scene = &given_scene; 
	}

	virtual void render(RenderWindow& renderer) = 0;

};
