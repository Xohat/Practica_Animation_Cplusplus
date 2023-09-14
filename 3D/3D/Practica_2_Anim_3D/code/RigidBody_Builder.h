/**
* @file RigidBody_Builder.h
* @brief Clase encargada de la creación de formas físicas
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
/// Clase encargada de la creación de formas físicas
/// </summary>
class RigidBody_Builder 
{

public:

    static shared_ptr< btRigidBody > create_ground
    (
        vector< shared_ptr< btRigidBody          > >& rigidBodies,
        vector< shared_ptr< btDefaultMotionState > >& motionStates,
        vector< shared_ptr< btCollisionShape     > >& collisionShapes,
        shared_ptr< btDiscreteDynamicsWorld >& dynamicsWorld,
        btVector3 scale
    )
    {
        {
            shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(0.1f, 1.f, 0.f)));

            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0, -4, 0));

            //------------------------------------Using motionstate is optional for static objects.------------------------------------

            shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
            btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get());
            shared_ptr< btRigidBody >                body(new btRigidBody(info));

            body->setRestitution(0.7f);

            body->setDeactivationTime(10000000);
            body->setActivationState(DISABLE_DEACTIVATION);
            body->setAngularFactor(btVector3(0.0, 0.0, 0.0));
            body->setGravity(btVector3(0, 0, 0));

            //------------------------------------Add the body to the dynamics world.------------------------------------

            dynamicsWorld->addRigidBody(body.get());

            //------------------------------------Save the smart pointers for automatic cleanup.------------------------------------

            rigidBodies.push_back(body);
            motionStates.push_back(state);
            collisionShapes.push_back(shape);

            return body;
        }
    }
    
    //------------------------------------CREA LOS CUERPOS FÍSICOS------------------------------------

    static shared_ptr< btRigidBody > create_box
    (
        vector< shared_ptr< btRigidBody          > >& rigidBodies,
        vector< shared_ptr< btDefaultMotionState > >& motionStates,
        vector< shared_ptr< btCollisionShape     > >& collisionShapes,
        shared_ptr< btDiscreteDynamicsWorld >       & dynamicsWorld,
        btVector3 scale
    )

    {
        shared_ptr<btRigidBody> cube_body;

        {
            // Se crea la forma
            shared_ptr<btCollisionShape> shape(new btBoxShape(scale));

            // Se crea su transform
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0., 5., 0.));

            // Su masa e inercia
            btScalar mass = 1000000.f;
            btVector3 localInertia(0., 0., 0.);

            shape->calculateLocalInertia(mass, localInertia);

            // Se settean los limites físicos de la forma
            shared_ptr<btDefaultMotionState> state(new btDefaultMotionState(transform));
            btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

            cube_body.reset(new btRigidBody(info));

            cube_body->setRestitution(0.5);

            // Se impide que se quede sin recibir movimiento si se para durante un rato
            cube_body->setDeactivationTime(10000000);
            cube_body->setActivationState(DISABLE_DEACTIVATION);
            cube_body->setAngularFactor(btVector3(0.0, 0.0, 0.0));

            //------------------------------------Add the body to the dynamics world.------------------------------------

            dynamicsWorld->addRigidBody(cube_body.get());

            //------------------------------------Guardar los smart pointers para la limpieza automática.------------------------------------

            rigidBodies.push_back(cube_body);
            motionStates.push_back(state);
            collisionShapes.push_back(shape);

            return cube_body;
        }
    }

    static shared_ptr< btRigidBody > create_physic_sphere
    (
        vector< shared_ptr< btRigidBody          > >& rigidBodies,
        vector< shared_ptr< btDefaultMotionState > >& motionStates,
        vector< shared_ptr< btCollisionShape     > >& collisionShapes,
        shared_ptr< btDiscreteDynamicsWorld >       & dynamicsWorld,
        btVector3 scale
    ) 

    {
        //------------------------------------DYNAMIC OBJECT SPHERE------------------------------------

        shared_ptr< btRigidBody > sphere_body;

        {
            // Se crea la forma
            shared_ptr< btCollisionShape > shape(new btSphereShape(btScalar(1.f)));

            // Se crea su transform
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0, 10, 0));

            // Su masa e inercia
            btScalar  mass = 1.f;
            btVector3 localInertia(0, 0, 0);

            shape->calculateLocalInertia(mass, localInertia);

            // Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            // Se settean los limites físicos de la forma

            shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
            btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

            sphere_body.reset(new btRigidBody(info));

            sphere_body->setRestitution(1.0);

            // Se impide que se quede sin recibir movimiento si se para durante un rato
            sphere_body->setDeactivationTime(10000000);
            sphere_body->setActivationState(DISABLE_DEACTIVATION);
            sphere_body->setAngularFactor(btVector3(0.0, 0.0, 0.0));

            //sphere_body->setGravity(btVector3(0, -10, 0));

            // Se añade el cuerpo al dynamic world
            dynamicsWorld->addRigidBody(sphere_body.get());

            //------------------------------------Guardar los smart pointers para la limpieza automática.------------------------------------

            rigidBodies.push_back(sphere_body);
            motionStates.push_back(state);
            collisionShapes.push_back(shape);

            return sphere_body;
        }
    }
};