// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

/// <summary>
/// Encargada del manejo del player
/// </summary>
/// <param name="player"></param>
class Player 
{
	b2Body* body;
	b2BodyDef* bodyDef;

public:

	Player(b2World& given_world) 
	{
		body = given_world.CreateBody(bodyDef);
	}

	void set_position() 
	{
		body;
	}

	b2Body* get_body()
	{
		return body;
	}
};