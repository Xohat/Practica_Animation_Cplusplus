/**
* @file Scene.h
* @brief Clase encargada del manejo de la escena, debido a problemas se ha quedado sin funcionalidad
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
/// Clase encargada del manejo de la escena, debido a problemas se ha quedado sin funcionalidad
/// </summary>
class Scene 
{
	shared_ptr< Render_Node > visual_scene;
	shared_ptr< Camera      > visual_camera;
	shared_ptr< Light       > visual_light;

	GLsizei width;
	GLsizei height;

    void configure_visual_scene(Render_Node& scene)
    {
        scene["light"]->translate(Vector3(10.f, 10.f, 10.f));
        scene["camera"]->translate(Vector3(0.f, 0.f, 5.f));
    }

    void reset_visual_viewport(const sf::Window& window, Render_Node& scene)
    {
        GLsizei width = GLsizei(window.getSize().x);
        GLsizei height = GLsizei(window.getSize().y);

        scene.get_active_camera()->set_aspect_ratio(float(width) / height);

        glViewport(0, 0, width, height);
    }

};