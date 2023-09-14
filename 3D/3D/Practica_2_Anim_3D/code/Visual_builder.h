/**
* @file Visual_builder.h
* @brief Clase encargada de la creación de formas visuales en base a las físicas
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "RigidBody_Builder.h"

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

/// <summary>
/// Clase encargada de la creación de formas visuales en base a las físicas
/// </summary>
class Visual_buidler 
{

public:

	/// <summary>
	/// Construye la forma visual de la entidad física, en este caso una esfera
	/// </summary>
	/// <param name="scene"></param>
	/// <param name="model_path"></param>
	/// <param name="model_name"></param>
	/// <returns></returns>
	static shared_ptr < Model > circle_model
	(
		shared_ptr< Render_Node > scene,
		std::string model_path,
		std::string model_name
	) 
	{
		shared_ptr< Model > model (new Model_Obj(model_path));

		scene->add(model_name, model);

		return model;
	}

	/// <summary>
	/// Construye la forma visual de la entidad física, en este caso un cubo
	/// </summary>
	/// <param name="scene"></param>
	/// <param name="model_path"></param>
	/// <param name="model_name"></param>
	/// <param name="scale"></param>
	/// <returns></returns>
	static shared_ptr < Model > cube_model
	(
		shared_ptr< Render_Node > scene,
		std::string model_path,
		std::string model_name,
		btVector3 scale
	)
	{
		shared_ptr< Model > model(new Model_Obj(model_path));
		
		scene->add(model_name, model);

		return model;
	}
};