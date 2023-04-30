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