//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2016.04+
//

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace
{

    /** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde superior.
      * Esta función se encarga de convertir el sistema de coordenadas para que la escena no se vea invertida.
      */
    inline Vector2f box2d_position_to_sfml_position (const b2Vec2 & box2d_position, float window_height, float scale)
    {
        return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
    }

    unique_ptr< b2World > create_physics_world ()
    {
        // Se crea el mundo físico:

        unique_ptr< b2World > physics_world
        {
            new b2World{ b2Vec2{ 0, -10.f } }
        };

        // CÍRCULO
        {
            // Se crea el body a partir de una definición de sus características:

            b2BodyDef body_definition;

            body_definition.type = b2_dynamicBody;
            body_definition.position.Set (4, 3);                                    // Posición inicial absoluta

            b2Body * body = physics_world->CreateBody (&body_definition);

            // Se añande una fixture al body:

            b2CircleShape body_shape;

            body_shape.m_radius = .5f;

            b2FixtureDef body_fixture;

            body_fixture.shape       = &body_shape;
            body_fixture.density     = 1.00f;
            body_fixture.restitution = 0.75f;
            body_fixture.friction    = 0.50f;

            body->CreateFixture (&body_fixture);
        }

        // CUADRADO
        {
            // Se crea el body a partir de una definición de sus características:

            b2BodyDef body_definition;

            body_definition.type = b2_dynamicBody;
            body_definition.position.Set (4, 5);                                    // Posición inicial absoluta
            body_definition.angle = 0.75f;

            b2Body * body = physics_world->CreateBody (&body_definition);

            // Se añande una fixture al body:

            b2PolygonShape body_shape;

            body_shape.SetAsBox (.5f, .5f);

            b2FixtureDef body_fixture;

            body_fixture.shape       = &body_shape;
            body_fixture.density     = 1.00f;
            body_fixture.restitution = 0.50f;
            body_fixture.friction    = 0.50f;

            body->CreateFixture (&body_fixture);
        }

        // SUELO
        {
            // Se crea el body a partir de una definición de sus características:

            b2BodyDef body_definition;

            body_definition.type = b2_staticBody;
            body_definition.position.Set (0.f, 1.f);                                // Posición inicial absoluta
            body_definition.angle = 0.f;

            b2Body * body = physics_world->CreateBody (&body_definition);

            // Se añande una fixture al body:

            b2EdgeShape body_shape;

            body_shape.SetTwoSided (b2Vec2(0.f, 1.f), b2Vec2(10, 1.f));                     // Coordenadas locales respecto al centro del body

            b2FixtureDef body_fixture;

            body_fixture.shape = &body_shape;

            body->CreateFixture (&body_fixture);
        }

        return physics_world;
    }

    void render (b2World & physics_world, RenderWindow & window, float scale)
    {
        // Se cachea el alto de la ventana en una variable local:

        float window_height = (float)window.getSize ().y;

        // Se recorre toda la lista de bodies de physics_world:

        for (b2Body * body = physics_world.GetBodyList (); body != nullptr; body = body->GetNext ())
        {
            // Se obtiene el transform del body:

            const b2Transform & body_transform = body->GetTransform ();

            // Se recorre la lista de fixtures del body:

            for (b2Fixture * fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext ())
            {
                // Se obtiene el tipo de forma de la fixture:

                b2Shape::Type shape_type = fixture->GetShape ()->GetType ();

                if (shape_type == b2Shape::e_circle)
                {
                    // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                    // En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
                    // del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                    b2CircleShape * circle = dynamic_cast< b2CircleShape * >(fixture->GetShape ());

                    float  radius = circle->m_radius * scale;
                    b2Vec2 center = circle->m_p;

                    CircleShape shape;

                    shape.setPosition  (box2d_position_to_sfml_position (b2Mul (body_transform, center), window_height, scale) - Vector2f(radius, radius));
                    shape.setFillColor (Color::Blue);
                    shape.setRadius    (radius);

                    window.draw (shape);
                }
                else
                if (shape_type == b2Shape::e_edge)
                {
                    // Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
                    // Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                    // que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
                    // partir de datos de vértices.

                    b2EdgeShape * edge = dynamic_cast< b2EdgeShape * >(fixture->GetShape ());

                    b2Vec2 start = b2Mul (body_transform, edge->m_vertex1);
                    b2Vec2 end   = b2Mul (body_transform, edge->m_vertex2);

                    Vertex line[] =
                    {
                        Vertex(box2d_position_to_sfml_position (start, window_height, scale), Color::Green),
                        Vertex(box2d_position_to_sfml_position (  end, window_height, scale), Color::Green),
                    };

                    window.draw (line, 2, Lines);
                }
                else
                if (shape_type == b2Shape::e_polygon)
                {
                    // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                    // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                    b2PolygonShape * box2d_polygon = dynamic_cast< b2PolygonShape * >(fixture->GetShape ());
                    ConvexShape       sfml_polygon;

                    int number_of_vertices = box2d_polygon->m_count;

                    sfml_polygon.setPointCount (number_of_vertices);
                    sfml_polygon.setFillColor  (Color::Yellow);

                    for (int index = 0; index < number_of_vertices; index++)
                    {
                        sfml_polygon.setPoint
                        (
                            index, 
                            box2d_position_to_sfml_position (b2Mul (body_transform, box2d_polygon->m_vertices[index]), window_height, scale)
                        );
                    }

                    window.draw (sfml_polygon);
                }
            }
        }
    }
}

int main ()
{
    RenderWindow window(VideoMode(800, 600), "Box2D Intro", Style::Titlebar | Style::Close, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    auto  physics_world = create_physics_world ();

    const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

    const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada
    
    float delta_time = target_time;                     // Previsión de la duración del fotograma actual
    bool  running    = true;

    Clock timer;

    do
    {
        timer.restart ();

        // Process window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update:

        physics_world->Step (delta_time, 8, 4);

        // Render:

        window.clear ();

        render (*physics_world, window, physics_to_graphics_scale);

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
    while (running);

    return EXIT_SUCCESS;
}
