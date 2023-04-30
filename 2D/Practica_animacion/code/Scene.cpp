#include "Scene.h"

void Scene::process_events() 
{
	Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
			{
				break;
			}

			case Event::KeyPressed:
			{
				switch (event.key.code)
				{
					// Force inputs
				case Keyboard::Key::A:
					break;

				case Keyboard::Key::D:
					break;

					// Jump imput
				case Keyboard::Key::Space:
					break;
				}
			}
		}
	}
}