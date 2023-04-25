//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Click: crear nuevo objeto.
//

#include <ciso646>
#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace
{

    /** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde
      * superior. Esta función se encarga de convertir el sistema de coordenadas para que la escena
      * no se vea invertida.
      */
    inline Vector2f box2d_position_to_sfml_position (const b2Vec2 & box2d_position, float window_height, float scale)
    {
        return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
    }

    // ------------------------------------------------------------------------------------------ //

    inline b2Vec2 sfml_position_to_box2d_position (const Vector2f & sfml_position, float window_height, float scale)
    {
        return b2Vec2(sfml_position.x / scale, (window_height - sfml_position.y) / scale);
    }

    // ------------------------------------------------------------------------------------------ //

    b2Body * create_circle (b2World & physics_world, b2BodyType body_type, float x, float y, float radius)
    {
        // Se crea el body:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set (x, y);                            // Posición inicial absoluta

        b2Body * body = physics_world.CreateBody (&body_definition);

        // Se añande una fixture:

        b2CircleShape body_shape;

        body_shape.m_radius = radius;

        b2FixtureDef body_fixture;

        body_fixture.shape       = &body_shape;
        body_fixture.density     = 0.10f;
        body_fixture.restitution = 0.75f;
        body_fixture.friction    = 0.50f;

        body->CreateFixture (&body_fixture);

        return body;
    }

    // ------------------------------------------------------------------------------------------ //

    b2Body * create_box (b2World & physics_world, b2BodyType body_type, float x, float y, float width, float height)
    {
        // Se crea el body:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set (x, y);                            // Posición inicial absoluta

        b2Body * body = physics_world.CreateBody (&body_definition);

        // Se añande una fixture:

        b2PolygonShape body_shape;

        body_shape.SetAsBox (width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape       = &body_shape;
        body_fixture.density     = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction    = 0.50f;

        body->CreateFixture (&body_fixture);

        return body;
    }

    // ------------------------------------------------------------------------------------------ //

    b2Body * create_edge (b2World & physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1)
    {
        // Se crea el body:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set (0.f, 0.f);                        // Posición inicial absoluta

        b2Body * body = physics_world.CreateBody (&body_definition);

        // Se añande una fixture:

        b2EdgeShape body_shape;

        body_shape.SetTwoSided (b2Vec2(x0, y0), b2Vec2(x1, y1));        // Coordenadas locales respecto al centro del body

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;

        body->CreateFixture (&body_fixture);

        return body;
    }

    // ------------------------------------------------------------------------------------------ //

    b2RevoluteJoint * create_revolute_joint (b2World & physics_world, b2Body * body_a, b2Body * body_b, bool enable_motor = false)
    {
        b2RevoluteJointDef joint_def;

        joint_def.bodyA            = body_a;
        joint_def.bodyB            = body_b;
        joint_def.enableMotor      = enable_motor;
        joint_def.collideConnected = false;

        return dynamic_cast< b2RevoluteJoint * >(physics_world.CreateJoint (&joint_def));
    }

    // ------------------------------------------------------------------------------------------ //

    void render_circle
    (
        b2Vec2              center,
        float               radius, 
        const b2Transform & transform, 
        RenderWindow      & renderer, 
        float               window_height, 
        float               scale
    )
    {
        CircleShape shape;

        radius *= scale;

        shape.setPosition  (box2d_position_to_sfml_position (b2Mul (transform, center), window_height, scale) - Vector2f(radius, radius));
        shape.setRadius    (radius);
        shape.setFillColor (Color::Blue);

        renderer.draw (shape);
    }

    // ------------------------------------------------------------------------------------------ //

    void render_segment
    (
        const Vector2f & start, 
        const Vector2f & end, 
        const Color    & color,
        RenderWindow   & renderer
    )
    {
        Vertex line[] =
        {
            Vertex(start, color),
            Vertex(  end, color),
        };

        renderer.draw (line, 2, Lines);
    }

    // ------------------------------------------------------------------------------------------ //

    void render_segment
    (
        b2Vec2              start, 
        b2Vec2              end, 
        const b2Transform & transform, 
        RenderWindow      & renderer, 
        float               window_height, 
        float               scale
    )
    {
        start = b2Mul (transform, start);
        end   = b2Mul (transform, end);

        render_segment 
        (
            box2d_position_to_sfml_position (start, window_height, scale),
            box2d_position_to_sfml_position (  end, window_height, scale),
            Color::Green,
            renderer
        );
    }

    // ------------------------------------------------------------------------------------------ //

    void render_polygon
    (
        const b2Vec2      * vertices,
        int                 number_of_vertices,
        const b2Transform & transform,
        RenderWindow      & renderer,
        float               window_height,
        float               scale
    )
    {
        ConvexShape sfml_polygon;

        sfml_polygon.setPointCount (number_of_vertices);
        sfml_polygon.setFillColor  (Color::Yellow);

        for (int index = 0; index < number_of_vertices; index++)
        {
            sfml_polygon.setPoint
            (
                index, 
                box2d_position_to_sfml_position (b2Mul (transform, vertices[index]), window_height, scale)
            );
        }

        renderer.draw (sfml_polygon);
    }

    // ------------------------------------------------------------------------------------------ //

    void render (b2World & physics_world, RenderWindow & renderer, float scale)
    {
        // Se cachea el alto de la ventana en una variable local:

        float window_height = (float)renderer.getSize ().y;

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

                switch (shape_type)
                {
                    case b2Shape::e_circle:
                    {
                        // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                        // En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
                        // del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                        b2CircleShape * circle = dynamic_cast< b2CircleShape * >(fixture->GetShape ());

                        render_circle  (circle->m_p, circle->m_radius, body_transform, renderer, window_height, scale);

                        break;
                    }
                    case b2Shape::e_edge:
                    {
                        // Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
                        // Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                        // que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
                        // partir de datos de vértices.

                        b2EdgeShape   * edge = dynamic_cast< b2EdgeShape * >(fixture->GetShape ());

                        render_segment (edge->m_vertex1, edge->m_vertex2, body_transform, renderer, window_height, scale);

                        break;
                    }
                
                    case b2Shape::e_polygon:
                    {
                        // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                        // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                        b2PolygonShape * box2d_polygon = dynamic_cast< b2PolygonShape * >(fixture->GetShape ());

                        render_polygon  (box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale);

                        break;
                    }
                }
            }
        }
    }

    // ------------------------------------------------------------------------------------------ //

    bool process_events (Window & window, b2World & physics_world, float window_height, float scale)
    {
        Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case Event::MouseButtonPressed:
                {
                    b2Vec2 center = sfml_position_to_box2d_position
                    (
                        { float(event.mouseButton.x), float(event.mouseButton.y) }, window_height, scale
                    );

                    create_circle (physics_world, b2_dynamicBody, center.x, center.y, .5f);

                    break;
                }

                case Event::Closed:
                {
                    return true;
                }
            }
        }

        return false;
    }

}

int main ()
{
    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    RenderWindow window(VideoMode(window_width, window_height), "Box2D Joints", Style::Titlebar | Style::Close, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena física (de 8 x 6 metros):

    b2World physics_world{ b2Vec2{ 0, -10.f } };

    constexpr float left   = 0.01f;
    constexpr float right  = 8.00f;
    constexpr float top    = 6.00f;
    constexpr float bottom = 0.01f;

    create_edge (physics_world, b2_staticBody, left,  bottom, right, bottom);
    create_edge (physics_world, b2_staticBody, left,  bottom, left,  top   );
    create_edge (physics_world, b2_staticBody, left,  top,    right, top   );
    create_edge (physics_world, b2_staticBody, right, bottom, right, top   );

    auto * box_anchor   = create_box (physics_world, b2_staticBody , 4, 3, 0.2f, 0.2f);
    auto * box_platform = create_box (physics_world, b2_dynamicBody, 4, 3, 2.9f, 0.1f);
    auto * boxes_joint  = create_revolute_joint (physics_world, box_anchor, box_platform, true);

    boxes_joint->SetMaxMotorTorque (75.f);
    boxes_joint->SetMotorSpeed (1.f);

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

        exit = process_events (window, physics_world, window_height, physics_to_graphics_scale);

        // Update:

        physics_world.Step (delta_time, 8, 4);

        // Render:

        window.clear ();

        render (physics_world, window, physics_to_graphics_scale);

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