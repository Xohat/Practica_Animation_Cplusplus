//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
//

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Adapter 
{

public:

	/** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde
	  * superior. Esta función se encarga de convertir el sistema de coordenadas para que la escena
	  * no se vea invertida.
	 */

	inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
	{
		return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
	}

	// ------------------------------------------------------------------------------------------ //

	inline b2Vec2 sfml_position_to_box2d_position(const Vector2f& sfml_position, float window_height, float scale)
	{
		return b2Vec2(sfml_position.x / scale, (window_height - sfml_position.y) / scale);
	}
};