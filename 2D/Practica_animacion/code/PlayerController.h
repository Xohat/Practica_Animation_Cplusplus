// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include "Player.h"
#include <Box2D/Box2D.h>

using namespace sf;
using namespace std;

/// <summary>
/// Encargada del movimiento del player
/// </summary>
/// <param name="player"></param>
class PlayerController 
{
	Player player;
	float force;
	b2Vec2 vel;

	enum _moveState 
	{
		MS_STOP,
		MS_LEFT,
		MS_RIGHT,
		MS_JUMP
	};

	_moveState moveState;

public:

	PlayerController(Player& given_player) 
	{
		//player = given_player;
		//vel = player.get_body().GetLinearVelocity();
		force = 0;
	}

	/// <summary>
	/// Se encarga del movimiento en los ejes en base al moveState proporcionado
	/// </summary>
	/// <param name="player"></param>
	void move() 
	{
		switch (moveState)
		{
			case MS_LEFT: 
				vel.x = -5; break;

			case MS_STOP:
				vel.x = 0; break;

			case MS_RIGHT: 
				vel.x = 5; break;

			case MS_JUMP:
				vel.y = 5; break;
		}
		//player.get_body().SetLinearVelocity(vel);
	}
};