// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#include "Scene.h"
#include "Circle.h"
#include "Rectangle.h"

void Scene::process_events() 
{
	Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
			{
				exit = true;
				break;
			}

			case Event::KeyPressed:
			{
				switch (event.key.code)
				{
					// Force inputs
					case Keyboard::Key::A:
						break;

					case Keyboard::Key::D:
						break;

					// Jump imput
					case Keyboard::Key::Space:
						break;
				}
			}
		}
	}
}

void Scene::create_scene() 
{
	//Aqui irian todos los creates en base al mapa creadoo en el .h

	//b2BodyType body_type, float x, float y, float radius, float density, Scene *scene
	geometries["Circle"] = Circle::create(b2_dynamicBody, 10.f, 20.f, 5.f, 2.f, this);
	geometries["Rectangle"] = Rectangle::create(b2_kinematicBody, 0.f, 5.f, 40.f, 5.f, this);
}

void Scene::render() 
{
	for (auto& geometry : geometries)
	{
		geometry.second->render(*window);
	}
}