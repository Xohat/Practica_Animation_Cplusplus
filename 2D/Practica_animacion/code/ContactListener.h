/**
* @file ContactListener.h
* @brief Hija de b2ContactListener, se encarga de manejar las colisiones en la escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <Box2D/Box2D.h>

/// <summary>
/// Detector de colisiones
/// </summary>
/// <param name="contact"></param>
class ContactListener : public b2ContactListener
{

public:

    /// <summary>
    /// Detecta la colisión en base al user data proporcionado en el create de las dos partes
    /// </summary>
    /// <param name="contact"></param>
    void BeginContact(b2Contact* contact);

    /// <summary>
    /// Activada al acabar el contacto, resettea la posición de la plataforma asociada al sensor que era partícipe antes
    /// </summary>
    /// <param name="contact"></param>
    void EndContact(b2Contact* contact);
};