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
#include "Geometry.h"
#include <SFML/Window.hpp>

int main()
{
	RenderWindow window;
	Scene scene (window);

	scene.run();

	return 0;
}

/*
	int main ()
	{
		Scene scene(0, -10.f);
		Geometry geo;

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
		geo.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  bottom, right, bottom);
		geo.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  bottom, left,  top   );
		geo.create_edge (scene.get_gravity_physics_world(), b2_staticBody, left,  top,    right, top   );
		geo.create_edge (scene.get_gravity_physics_world(), b2_staticBody, right, bottom, right, top   );

		// Caja con linea
		auto * box_anchor   = geo.create_box (scene.get_gravity_physics_world(), b2_staticBody , 3, 3, 0.2f, 0.2f);
		auto * box_platform = geo.create_box (scene.get_gravity_physics_world(), b2_dynamicBody, 4, 3, 0.55f, 0.1f);
		auto * boxes_joint  = geo.create_revolute_joint (scene.get_gravity_physics_world(), box_anchor, box_platform, true);

		boxes_joint->SetMaxMotorTorque (75.f);
		boxes_joint->SetMotorSpeed (2.f);

		//boxes_joint->EnableMotor(false);

		const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

		// Se ejecuta el bucle principal de la animación:
    
		const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
		const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

		float delta_time = target_time;                     // Previsión de la duración del fotograma actual
		bool  exit       = false;

		Clock timer;



		return 0;
	}
*/