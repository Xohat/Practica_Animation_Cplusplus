/**
* @file Joints.h
* @brief Clase encargada del manejo de los Joints para el jugador principal
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "Geometry.h"

/// <summary>
/// Clase encargada del manejo de los Joints para el jugador principal
/// </summary>
class Joints 
{
    // ------------------------------------------------------------------------------------------ //

    static b2RevoluteJoint* create_revolute_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, bool enable_motor = false)
    {
        b2RevoluteJointDef joint_def;

        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;
        joint_def.enableMotor = enable_motor;
        joint_def.collideConnected = false;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }

    static b2RevoluteJoint* create_revolute_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool enable_motor = false)
    {
        b2RevoluteJointDef joint_def;

        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;
        joint_def.enableMotor = enable_motor;
        joint_def.collideConnected = false;

        joint_def.localAnchorA = localAnchorA;
        joint_def.localAnchorB = localAnchorB;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }
    static b2WeldJoint* create_weld_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, b2Vec2 localAnchorA, b2Vec2 localAnchorB)
    {
        b2WeldJointDef joint_def;

        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;
        joint_def.collideConnected = false;

        joint_def.localAnchorA = localAnchorA;
        joint_def.localAnchorB = localAnchorB;

        return dynamic_cast<b2WeldJoint*>(physics_world.CreateJoint(&joint_def));
    }
};