#include "ContactListener.h"

#include "Rectangle_platform.h"
#include "Collision_sensor.h"
#include "Fire.h"
#include "Player.h"

/// <summary>
/// Detecta la colisión en base al user data proporcionado en el create de las dos partes
/// </summary>
/// <param name="contact"></param>
void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    // Check if either fixture is a sensor
    bool sensorA = fixture_a->IsSensor();
    bool sensorB = fixture_b->IsSensor();

    if (!(sensorA || sensorB)) { return; }

    // Obtener el UserData y convertirlo al tipo adecuado
    Geometry* userdata_a = reinterpret_cast<Geometry*>(fixture_a->GetUserData().pointer);
    Geometry* userdata_b = reinterpret_cast<Geometry*>(fixture_b->GetUserData().pointer);
    
    //// Comprobar si la colisión es entre la plataforma y el jugador
    //if (dynamic_cast<Collision_Sensor*>(userdata_a) && dynamic_cast<Player*>(userdata_b))
    //{
    //    // Realizar la lógica de movimiento de la plataforma
    //    Collision_Sensor* platform = static_cast<Collision_Sensor*>(userdata_a);
    //    //platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
    //}
    //else if (dynamic_cast<Player*>(userdata_a) && dynamic_cast<Collision_Sensor*>(userdata_b))
    //{
    //    // Realizar la lógica de movimiento de la plataforma (si también quieres detectar cuando el jugador colisiona con la plataforma)
    //    Collision_Sensor* platform = static_cast<Collision_Sensor*>(userdata_b);
    //    //platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
    //}  

    //if (dynamic_cast<Fire*>(userdata_a) && dynamic_cast<Player*>(userdata_b))
    //{
    //    //scene->reset_scene();
    //}
    //else if (dynamic_cast<Player*>(userdata_a) && dynamic_cast<Fire*>(userdata_b))
    //{
    //    //scene->reset_scene();
    //}
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    // Obtener el UserData y convertirlo al tipo adecuado
    Geometry* userdata_a = reinterpret_cast<Geometry*>(fixture_a->GetUserData().pointer);
    Geometry* userdata_b = reinterpret_cast<Geometry*>(fixture_b->GetUserData().pointer);

    //// Comprobar si la colisión es entre la plataforma y el jugador
    //if (dynamic_cast<Collision_Sensor*>(userdata_a) && dynamic_cast<Player*>(userdata_b))
    //{
    //    // Realizar la lógica de movimiento de la plataforma
    //    Collision_Sensor* platform = static_cast<Collision_Sensor*>(userdata_a);
    //    //platform->update_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
    //}
    //else if (dynamic_cast<Player*>(userdata_a) && dynamic_cast<Collision_Sensor*>(userdata_b))
    //{
    //    // Realizar la lógica de movimiento de la plataforma (si también quieres detectar cuando el jugador colisiona con la plataforma)
    //    Collision_Sensor* platform = static_cast<Collision_Sensor*>(userdata_b);
    //    //platform->reset_movement(0.016f); // La plataforma se moverá hacia arriba durante 1/60 segundos (60 fps)
    //}
}