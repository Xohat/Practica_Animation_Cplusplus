// Copyright (C) 2023
// Hecho por Arturo Vilar Carretero
// 2023.4+

#pragma once

#include <Box2D/Box2D.h>
#include "Rectangle_platform.h"

/// <summary>
/// Detector de colisiones
/// </summary>
/// <param name="contact"></param>
class ContactListener : public b2ContactListener
{
    /// <summary>
    /// Detecta la colisión en base al user data proporcionado en el create de las dos partes
    /// </summary>
    /// <param name="contact"></param>
    void BeginContact(b2Contact* contact)
    {
        b2Fixture* fixture_a = contact->GetFixtureA();
        b2Fixture* fixture_b = contact->GetFixtureB();

        // Obtener el UserData y convertirlo al tipo adecuado
        std::string userdata_a = *reinterpret_cast<std::string*>(fixture_a->GetUserData().pointer);
        std::string userdata_b = *reinterpret_cast<std::string*>(fixture_b->GetUserData().pointer);

        /*
        // Comprobar si la colisión es entre la plataforma y el jugador
        if (userdata_a == "up_platform" && userdata_b == "player")
        {
            // Realizar la lógica de movimiento de la plataforma
            Rectangle_Platform* platform = static_cast<Rectangle_Platform*>(fixture_a->GetBody()->GetUserData());
            platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
        }
        else if (userdata_a == "player" && userdata_b == "up_platform")
        {
            // Realizar la lógica de movimiento de la plataforma (si también quieres detectar cuando el jugador colisiona con la plataforma)
            Rectangle_Platform* platform = static_cast<Rectangle_Platform*>(fixture_b->GetBody()->GetUserData());
            platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
        }
        */
    }
};