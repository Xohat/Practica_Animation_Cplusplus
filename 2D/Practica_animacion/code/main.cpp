//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
//

#include "Scene.h"
#include <SFML/Window.hpp>

int main ()
{
	Scene scene(0, -10.f);

    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    RenderWindow window(VideoMode(window_width, window_height), "Box2D Joints", Style::Titlebar | Style::Close, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena física (de 8 x 6 metros):

    constexpr float left   = 0.01f;
    constexpr float right  = 8.00f;
    constexpr float top    = 6.00f;
    constexpr float bottom = 0.01f;

	// Se crean los bordes de la pantalla
	scene.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  bottom, right, bottom);
	scene.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  bottom, left,  top   );
	scene.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  top,    right, top   );
	scene.create_edge (scene.get_gravity_physics_world(), b2_staticBody, right, bottom, right, top   );

	// Caja con linea
    auto * box_anchor   = scene.create_box (scene.get_gravity_physics_world(), b2_staticBody , 3, 3, 0.2f, 0.2f);
    auto * box_platform = scene.create_box (scene.get_gravity_physics_world(), b2_dynamicBody, 4, 3, 1.1f, 0.1f);
    auto * boxes_joint  = scene.create_revolute_joint (scene.get_gravity_physics_world(), box_anchor, box_platform, true);

    boxes_joint->SetMaxMotorTorque (75.f);
    boxes_joint->SetMotorSpeed (2.f);

	//boxes_joint->EnableMotor(false);

	auto* box_test = scene.create_box(scene.get_gravity_physics_world(), b2_dynamicBody, 4, 3, 2.9f, 0.1f);
	box_test->SetTransform({ 5.f, 1.f }, 0);

	/*
	 	auto* box_test = scene.create_box(physics_world, b2_dynamicBody, 4, 3, 2.9f, 0.1f);
		box_test->SetTransform({ 5.f, 1.f }, 0);

		auto* box_test_2 = scene.create_box(physics_world, b2_dynamicBody, 4, 3, 2.f, 0.1f);
		box_test->SetTransform({ 5.f, 1.5f }, 0);
	*/

    const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

    // Se ejecuta el bucle principal de la animación:
    
    const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

    float delta_time = target_time;                     // Previsión de la duración del fotograma actual
    bool  exit       = false;

    Clock timer;

    do
    {
        timer.restart ();

        // Process window events:

        exit = scene.process_events (window, scene.get_gravity_physics_world(), window_height, physics_to_graphics_scale);

        // Update:

		scene.get_gravity_physics_world().Step (delta_time, 8, 4);

        // Render:

        window.clear ();

		scene.render (scene.get_gravity_physics_world(), window, physics_to_graphics_scale);

        window.display ();

        // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
        // fotogramas por segundo deseada:

        float elapsed = timer.getElapsedTime ().asSeconds ();

        if (elapsed < target_time)
        {
            sleep (seconds (target_time - elapsed));
        }

        // Se restablece la estimación de la duración del siguiente fotograma:

        delta_time = timer.getElapsedTime ().asSeconds ();
    }
    while (not exit);

    return 0;
}