/**
* @file Entity.h
* @brief Clase encargada de ser la clase padre de todos los elementos visuales y físicos de la escena, al almacenar los tipos por el constructor
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

using namespace std;
using namespace glt;

/// <summary>
/// Clase encargada de ser la clase padre de todos los elementos visuales 
/// y físicos de la escena, al almacenar los tipos por el constructor
/// </summary>
class Entity 
{

public:

    /// <summary>
    /// Escala visual
    /// </summary>
    btVector3 visual_scale{0.f, 0.f, 0.f};

	/// <summary>
	/// Referencia a un modelo
	/// </summary>
	shared_ptr< Model       > model;
	/// <summary>
	/// Referencia a un rigidbody
	/// </summary>
	shared_ptr< btRigidBody > rigid_body;

    /// <summary>
    /// Enum para la definición de tipos de la plataforma
    /// </summary>
    enum Entity_type
    {
        GROUND = 0,
        PLATFORM = 1,
        PLAYER = 2,
        KEY = 3,
        DOOR = 4
    };

    /// <summary>
    /// Bool para la colisión
    /// </summary>
    bool vertical_platform_collision;

    /// <summary>
    /// Bool para la colisión
    /// </summary>
    bool key_collision;

    /// <summary>
    /// Bool para la colisión
    /// </summary>
    bool door_collision;

    /// <summary>
    /// Variable clave para poder romper la puerta
    /// </summary>
    bool has_key;

    /// <summary>
    /// Usado para el movimiento de la plataforma vertical
    /// </summary>
    int direction = 1;

    /// <summary>
    /// Tipo del objeto
    /// </summary>
    Entity_type type;

	/// <summary>
	/// Constructor de entidad
	/// </summary>
	/// <param name="given_rigid_body"></param>
	/// <param name="given_model"></param>
	Entity(shared_ptr< btRigidBody > given_rigid_body, shared_ptr< Model > given_model)
	{
		rigid_body = given_rigid_body;
		model = given_model;

        given_rigid_body->setUserPointer((void*)(this));
	}

    /// <summary>
    /// Settea el tipo del objeto, para asi pdoer hacer uso de los mismos en colisiones
    /// </summary>
    /// <param name="type_number"></param>
    void set_type(int type_number) 
    {
        switch (type_number)
        {
            case 0:
                type = GROUND;
                break;
            case 1:
                type = PLATFORM;
                break;
            case 2:
                type = PLAYER;
                break;
            case 3:
                type = KEY;
                break;
           case 4:
                type = DOOR;
                break;
            default:
                break;
        }
    }

    /// <summary>
    /// Obitiene el tipo del objeto
    /// </summary>
    /// <returns></returns>
    Entity_type get_type()
    {
        return type;
    }

    /// <summary>
    /// Mueve la plataforma vertical hacia arriba
    /// </summary>
    /// <param name="start_position"></param>
    void move_vertical_up (btVector3 start_position) 
    {
        btTransform currentTransform = rigid_body->getWorldTransform();
        float current_y = currentTransform.getOrigin().getY();
        float target_y = 1.f;

        // Variable para rastrear la dirección actual del movimiento
        int direction = (current_y < target_y) ? 1 : -1;

        // Si la posición actual es menor que la posición objetivo y la dirección es positiva (subiendo)
        if (current_y < target_y && direction == 1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 2, 0));
        }
        // Si la posición actual es mayor o igual que la posición objetivo y la dirección es positiva (subiendo)
        else if (current_y >= target_y && direction == 1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 0, 0)); // Detiene el movimiento vertical
            direction = -1; // Cambia la dirección a negativa (bajando)
        }
        // Si la posición actual es mayor que la posición inicial y la dirección es negativa (bajando)
        else if (current_y > start_position.getY() && direction == -1)
        {
            rigid_body->setLinearVelocity(btVector3(0, -2, 0));
        }
        // Si la posición actual es menor o igual que la posición inicial y la dirección es negativa (bajando)
        else if (current_y <= start_position.getY() && direction == -1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 0, 0)); // Detiene el movimiento vertical
        }
    }

    /// <summary>
    /// Mueve la plataforma vertical hacia abajo
    /// </summary>
    /// <param name="start_position"></param>
    void move_vertical_down (btVector3 start_position)
    {
        btTransform currentTransform = rigid_body->getWorldTransform();
        float current_y = currentTransform.getOrigin().getY();

        // Variable para rastrear la dirección actual del movimiento
        int direction = (current_y > start_position.getY()) ? -1 : 1;

        // Si la posición actual es mayor que la posición objetivo y la dirección es negativa (bajando)
        if (current_y > start_position.getY() && direction == -1)
        {
            rigid_body->setLinearVelocity(btVector3(0, -2, 0));
        }
        // Si la posición actual es menor o igual que la posición objetivo y la dirección es negativa (bajando)
        else if (current_y <= start_position.getY() && direction == -1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 0, 0)); // Detiene el movimiento vertical
            direction = 1; // Cambia la dirección a positiva (subiendo)
        }
        // Si la posición actual es menor que la posición inicial y la dirección es positiva (subiendo)
        else if (current_y < start_position.getY() && direction == 1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 2, 0));
        }
        // Si la posición actual es mayor o igual que la posición inicial y la dirección es positiva (subiendo)
        else if (current_y >= start_position.getY() && direction == 1)
        {
            rigid_body->setLinearVelocity(btVector3(0, 0, 0)); // Detiene el movimiento vertical
        }
    }   

    /// <summary>
    /// Mueve la plataforma horizontal hacia abajo
    /// </summary>
    /// <param name="start_position"></param>
    void move_horizontal (btVector3 start_position)
    {
        btTransform currentTransform = rigid_body->getWorldTransform();

        float test_x = rigid_body->getWorldTransform().getOrigin().getX();
        float test_y = rigid_body->getWorldTransform().getOrigin().getY();  

        float velocity = 3;

        if (test_x < start_position.getX())
        {
            direction = 1;
        }
        if (test_x > 3.f)
        {
            direction = -1;
        }

        if (test_y < 4)
        {
            rigid_body->setLinearVelocity(btVector3(direction * velocity, 1, 0));
        }
        else
        {
            rigid_body->setLinearVelocity(btVector3(direction * velocity, 0, 0));
        }
    }

	/// <summary>
	/// Axcctualiza la posición visual en base a las físicas
	/// </summary>
	void update_visual_position() 
	{
		btTransform physics_transform;

		rigid_body->getMotionState()->getWorldTransform(physics_transform);

		glm::mat4 graphics_transform;

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		model->set_transformation(graphics_transform);

        if (visual_scale.getX() != 0.f)
        {
            model->scale(visual_scale.getX(), visual_scale.getY(), visual_scale.getZ());
        }
	}

    /// <summary>
    /// Configura la escala visual
    /// </summary>
    /// <param name="new_visual_scale"></param>
    void set_visual_scale (btVector3 new_visual_scale)
    {
        visual_scale = new_visual_scale;
    }

    /// <summary>
    /// Obtiene la escala visual
    /// </summary>
    /// <returns></returns>
    btVector3 get_visual_scale ()
    {
        return visual_scale;
    }
};