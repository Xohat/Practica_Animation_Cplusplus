/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
*/

#include <memory>
#include <vector>
#include <iostream>

#include "RigidBody_Builder.h"
#include "Visual_builder.h"
#include "Entity.h"
#include "ContactListener.h"

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

#include "Physics_world.h"

using namespace std;
using namespace glt;

namespace 
{
    shared_ptr< Render_Node > create_scene ()
    {
        //------------------------------------Se crean los elementos (nodos) y la escena a la que se a�adir�n:------------------------------------

        shared_ptr< Render_Node > scene      (new Render_Node);
        shared_ptr< Camera      > camera     (new Camera(20.f, 1.f, 50.f, 1.f));
        shared_ptr< Light       > light      (new Light);

        //------------------------------------Se a�aden los nodos a la escena:------------------------------------

        scene->add ("camera", camera);
        scene->add ("light" , light );

        return scene;
    }

    void configure_scene (Render_Node & scene)
    {
        scene["light" ]->translate (Vector3(10.f, 10.f, 10.f));
        scene["camera"]->translate (Vector3( 0.f,  0.f,  5.f));
    }

    void reset_viewport (const sf::Window & window, Render_Node & scene)
    {
        GLsizei width  = GLsizei(window.getSize ().x);
        GLsizei height = GLsizei(window.getSize ().y);

        scene.get_active_camera ()->set_aspect_ratio (float(width) / height);

        glViewport (0, 0, width, height);
    }
}

int main ()
{
#pragma region Physics_World_creation

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                       PHYSISCS WORLD INITIALIZATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    //------------------------------------Collision configuration contains default setup for memory, collision setup.------------------------------------
    //------------------------------------Advanced users can create their own configuration.------------------------------------

    btDefaultCollisionConfiguration collisionConfiguration;

    //------------------------------------Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).------------------------------------

    btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

    //------------------------------------btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.------------------------------------

    btDbvtBroadphase overlappingPairCache;

    //------------------------------------The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).------------------------------------

    btSequentialImpulseConstraintSolver constraintSolver;

    //------------------------------------Create and configure the physiscs world:------------------------------------

    shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld
    (
        new btDiscreteDynamicsWorld
        (
            &collisionDispatcher,
            &overlappingPairCache,
            &constraintSolver,
            &collisionConfiguration
        )
    );

    dynamicsWorld->setGravity (btVector3(0, -10, 0));

#pragma endregion

#pragma region Basic_Floor_RigidBody_Setup

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                            RIGID BODIES SETUP
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    //------------------------------------Keep track of the shapes, states and rigid bodies.------------------------------------
    //------------------------------------Make sure to reuse collision shapes among rigid bodies whenever possible!------------------------------------

    vector< shared_ptr< btRigidBody          > > rigidBodies;
    vector< shared_ptr< btDefaultMotionState > > motionStates;
    vector< shared_ptr< btCollisionShape     > > collisionShapes;

    // GROUND
    {
        shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(50, 1, 50)));

        btTransform transform;
        transform.setIdentity ();
        transform.setOrigin (btVector3(0, -4, 0));

        //------------------------------------Using motionstate is optional for static objects.------------------------------------

        shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
        btRigidBody::btRigidBodyConstructionInfo info (0, state.get (), shape.get ());
        shared_ptr< btRigidBody >                body (new btRigidBody(info));

        body->setRestitution (0.7f);

        body->setDeactivationTime(10000000);
        body->setActivationState(DISABLE_DEACTIVATION);
        body->setAngularFactor(btVector3(0.0, 0.0, 0.0));

        //------------------------------------Add the body to the dynamics world.------------------------------------

        dynamicsWorld->addRigidBody (body.get ());

        //------------------------------------Save the smart pointers for automatic cleanup.------------------------------------

        rigidBodies    .push_back (body );
        motionStates   .push_back (state);
        collisionShapes.push_back (shape);
    }

#pragma endregion

#pragma region Visual_setup

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                                SIMULATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    //------------------------------------Se crea la ventana y el contexto de OpenGL asociado a ella:------------------------------------

    sf::Window window
    (
        sf::VideoMode(1024, 720),
        "Bullet Rigid Bodies",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      //------------------------------------Se usa OpenGL 3.2 core profile------------------------------------
    );

    //------------------------------------Se determinan las caracter�sticas de OpenGL disponibles en la m�quina:------------------------------------

	if (!glt::initialize_opengl_extensions())
	{
		exit (-1);
	}

    //------------------------------Se activa la sincronizaci�n vertical:------------------------------------

    window.setVerticalSyncEnabled (true);

    //------------------------------Se crea y se configura la escena:------------------------------------

    shared_ptr< Render_Node > scene = create_scene ();

    configure_scene (*scene);

    // ------------------------------------Se inicializan algunos elementos de OpenGL:------------------------------------

    reset_viewport (window, *scene);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

#pragma endregion

#pragma region ENTITY_CREATION

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                            ENTITY CREATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    // Contact listener
    ContactCallback contact_listener;
    // Mapa de Entidades
    map < std::string, Entity*> entities;



    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rb_ground = RigidBody_Builder::create_ground (rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 10.f, 1.f, 5.f });
    shared_ptr<Model> model_ground = Visual_buidler::cube_model (scene, "../../assets/cube.obj", "Ground_test", { 10.f, 3.5f, 1.f });

    //rb_ground->getWorldTransform().setOrigin(btVector3(0, -4.5f, 0));

    Entity entidad_ground (rb_ground, model_ground);
    entities.insert(std::make_pair("Ground_test", &entidad_ground));
    entidad_ground.set_visual_scale({ 10.f, 3.5f, 1.f });

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rp = RigidBody_Builder::create_physic_sphere(rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 1.f, 1.f, 1.f });
    shared_ptr<Model> model = Visual_buidler::circle_model(scene, "../../assets/sphere.obj", "Cube_sphere_test");

    rp->getWorldTransform().setOrigin(btVector3{ -3.f, -1.f, 0.f });

    Entity entidad (rp, model);
    entities.insert(std::make_pair("Cube_sphere_test", &entidad));

    entidad.set_type(2);

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rp_platform_horizontal = RigidBody_Builder::create_box(rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 0.8f, 0.f, 0.1f });
    shared_ptr<Model> model_platform_horizontal = Visual_buidler::cube_model(scene, "../../assets/cube.obj", "Platform_horizontal_test", {5.f, 1.f, 1.f});

    rp_platform_horizontal->getWorldTransform().setOrigin(btVector3{ -3.5f, 2.f, 0.f });

    rp_platform_horizontal->setGravity({0,0,0});

    Entity entidad_platform_horizontal (rp_platform_horizontal, model_platform_horizontal);
    entities.insert(std::make_pair("Platform_horizontal_test", &entidad_platform_horizontal));

    entidad_platform_horizontal.set_visual_scale({ 2.f, 0.5f, 1.f });

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rp_platform_vertical = RigidBody_Builder::create_box(rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 0.8f, 0.f, 0.1f });
    shared_ptr<Model> model_platform_vertical = Visual_buidler::cube_model(scene, "../../assets/cube.obj", "Platform_vertical_test", { 5.f, 1.f, 1.f });

    rp_platform_vertical->getWorldTransform().setOrigin(btVector3{ 1.f, -1.25f, 0.f });

    rp_platform_vertical->setGravity({ 0,0,0 });

    Entity entidad_platform_vertical(rp_platform_vertical, model_platform_vertical);
    entities.insert(std::make_pair("Platform_vertical_test", &entidad_platform_vertical));

    entidad_platform_vertical.set_type(1);
    entidad_platform_vertical.set_visual_scale({ 2.f, 0.5f, 1.f });

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rp_key = RigidBody_Builder::create_box (rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 1.f, 1.f, 1.f });
    shared_ptr<Model> model_key = Visual_buidler::circle_model(scene, "../../assets/sphere.obj", "Key_test");

    rp_key->getWorldTransform().setOrigin(btVector3{ 4.f, -1.5f, 0.f });

    Entity entidad_key (rp_key, model_key);
    entities.insert(std::make_pair("Key_test", &entidad_key));

    entidad_key.set_type(3);

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    // Entidad, rigidbody y modelo
    shared_ptr<btRigidBody> rp_key_door = RigidBody_Builder::create_box(rigidBodies, motionStates, collisionShapes, dynamicsWorld, { 0.2f, 1.f, 1.f });
    shared_ptr<Model> model_key_door = Visual_buidler::cube_model(scene, "../../assets/cube.obj", "Key_door_test", { 3.f, 2.2f, 1.f });

    rp_key_door->getWorldTransform().setOrigin(btVector3{ 2.8f, -1.f, 0.f });

    Entity entidad_key_door(rp_key_door, model_key_door);
    entities.insert(std::make_pair("Key_door_test", &entidad_key_door));

    entidad_key_door.set_type(4);
    entidad_key_door.set_visual_scale({ 0.5f, 4.f, 1.f });

    // --------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma endregion

#pragma region Configracion_antes_del_update



    // Reiniciar la fuerza actual en cada iteración
    btVector3 current_force(0.0f, 0.0f, 0.0f);

    btVector3 start_position_horizontal = rp_platform_horizontal->getWorldTransform().getOrigin();
    btVector3 start_position_key = rp_key->getWorldTransform().getOrigin();
    btVector3 start_position_key_door = rp_key_door->getWorldTransform().getOrigin();
    btVector3 start_position_vertical = rp_platform_vertical->getWorldTransform().getOrigin();
#pragma endregion

#pragma region Update_Input

    //CICLO DE RUN
    do
    {
        // Read the user input:

        sf::Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

                case sf::Event::Resized:
                {
                    reset_viewport (window, *scene);
                    break;
                }
                
                case sf::Event::KeyReleased: 
                {
                    rp->clearForces();
                }

                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        // Force inputs
                        case sf::Keyboard::Key::A:
                        {
                            // FORCES

                            // Aplicar una fuerza hacia la izquierda a la esfera
                            btVector3 force(-10.0f, 0.0f, 0.0f);
                            rp->applyCentralForce(force);

                            break;
                        }

                        // Force inputs
                        case sf::Keyboard::Key::D:
                        {
                            // FORCES

                            // Aplicar una fuerza hacia la izquierda a la esfera
                            btVector3 force(10.0f, 0.0f, 0.0f);
                            rp->applyCentralForce(force);

                            break;
                        }

                        // Jump imput
                        case sf::Keyboard::Key::Space: 
                        {
                            btVector3 current_force = entidad.rigid_body->getTotalForce();
                            if (entidad.rigid_body->getWorldTransform().getOrigin().getY() <= btScalar(10.f))
                            {
                                // Apply an upward force to the sphere
                                btVector3 force(0.0f, 200.0f, 0.0f);
                                entidad.rigid_body->applyCentralForce(force);

                                break;
                            }
                            else
                            {
                                break;
                            }
                       }
                    }
                }
            }
        }
#pragma endregion

        ///--------------------SETUP-RENDER---------------------------------------

        // Perform the simulation:

        dynamicsWorld->stepSimulation (1.f / 60.f);

#pragma region Update_Actions

        //Test de colision
        for (auto& entity : entities)
        {
            if (entity.second->rigid_body != nullptr && entity.second->type != Entity::Entity_type::PLAYER)
            {
                dynamicsWorld->contactPairTest(entities["Cube_sphere_test"]->rigid_body.get(), entity.second->rigid_body.get(), contact_listener);
            }
        }
       
        btVector3 posi = entidad_platform_horizontal.rigid_body->getWorldTransform().getOrigin();
        entidad_platform_horizontal.rigid_body->getWorldTransform().setOrigin({ posi.getX(), start_position_horizontal.getY(), posi.getZ() });

        btVector3 posi_key = entidad_key.rigid_body->getWorldTransform().getOrigin();
        entidad_key.rigid_body->getWorldTransform().setOrigin({ start_position_key.getX(), start_position_key.getY(), posi_key.getZ() });

        entidad_platform_horizontal.move_horizontal(start_position_horizontal);

        btVector3 posi_door = entidad_key_door.rigid_body->getWorldTransform().getOrigin();
        entidad_key_door.rigid_body->getWorldTransform().setOrigin({ start_position_key_door.getX(), start_position_key_door.getY(), posi_door.getZ() });

        //
        if (entidad.vertical_platform_collision)
        {
            entidad_platform_vertical.move_vertical_up (start_position_vertical);
        }
        else 
        {    
            if (entidad_platform_vertical.rigid_body->getWorldTransform().getOrigin().getY() >= -1.25)
            {
                entidad_platform_vertical.rigid_body->setLinearVelocity(btVector3(0, -3, 0));
            }

            else
            {
                entidad_platform_vertical.rigid_body->setLinearVelocity(btVector3(0, 0, 0));
            }
        }

        if (entidad.key_collision) 
        {
            entidad.has_key = true;

            //No se destruir por lo que se va de pantalla y ya
            entidad_key.rigid_body->getWorldTransform().setOrigin({ posi_key.getX(), posi_key.getY() + 20.f, posi_key.getZ()});

            //Destroy entidad_key
        }

        if (entidad.door_collision) 
        {
            if (entidad.has_key) 
            {
                //No se destruir por lo que se va de pantalla y ya
                entidad_key_door.rigid_body->getWorldTransform().setOrigin({ posi_door.getX(), posi_door.getY() + 20.f, posi_door.getZ() });

                //Destroy entidad_door
            }
        }

        entidad.vertical_platform_collision = false;

        entidad.update_visual_position();
        entidad_key.update_visual_position();
        entidad_key_door.update_visual_position();

        entidad_platform_vertical.update_visual_position();
        entidad_platform_horizontal.update_visual_position();

        entidad_ground.update_visual_position();

#pragma endregion

        //------------------------------------Render the scene:------------------------------------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->render ();

        window.display ();
    }
    while (running);

    //------------------------------------Se debe destruir el mundo f�sico antes de que se destruyan los cuerpos r�gidos:------------------------------------

    dynamicsWorld.reset ();

    return EXIT_SUCCESS;
}
