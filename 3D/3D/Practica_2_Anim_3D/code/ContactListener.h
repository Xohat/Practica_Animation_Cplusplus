/**
* @file ContactListener.h
* @brief Clase encargada del manejo de colisiones, haciendo uso del ContactResultCallback de bullet
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "Entity.h"

/// <summary>
///  Clase encargada del manejo de colisiones, haciendo uso del ContactResultCallback de bullet
/// </summary>
class ContactCallback : public btCollisionWorld::ContactResultCallback 
{

public:

    virtual btScalar addSingleResult
    (
        btManifoldPoint& cp,
        const btCollisionObjectWrapper* collision_entity_0_wrapper,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* collision_entity_1_wrapper,
        int partId1,
        int index1
    )

    {
        // Obtener los objetos de colisión
        const btCollisionObject* entity_0_collision = collision_entity_0_wrapper->getCollisionObject();
        const btCollisionObject* entity_1_collision = collision_entity_1_wrapper->getCollisionObject();

        // Obtienes los user_pointers
        void* userPtr0 = entity_0_collision->getUserPointer();
        void* userPtr1 = entity_1_collision->getUserPointer();

        // Creas unos unos punteros entidad en base a un casteo a los userPtr
        Entity* entity_1 = (Entity*)userPtr0;
        Entity* entity_2 = (Entity*)userPtr1;

        // Variables usadas para simplemente 
        Entity* player = nullptr;
        Entity* player_collision = nullptr;

        // Discierne cual es el objeto y cual el player gracias al type
        if (entity_1->type == Entity::Entity_type::PLAYER)
        {
            player = entity_1;
            player_collision = entity_2;
        }
        if (entity_2->type == Entity::Entity_type::PLAYER)
        {
            player = entity_2;
            player_collision = entity_1;
        }

        // Si en el choque hay un player
        if (player != nullptr)
        {   
            // Se revisa el tipo de la colisión
            switch (player_collision->type)
            {
                // Si es de tipo KEY
                case Entity::Entity_type::KEY:

                    player->key_collision = true;
                    break;
                // Si es de tipo PLATFORM
                case Entity::Entity_type::PLATFORM:

                    player->vertical_platform_collision = true;
                    break;
                // Si es de tipo DOOR
                case Entity::Entity_type::DOOR:

                    player->door_collision = true;
                    break;
            }  

            // Print information about the collision

            std::cout << "Collision detected between objects with user pointers: " << userPtr0 << " and " << userPtr1 << std::endl;

            // Return 0 to process all contacts
            return 0;
        }
    }
};
