
class Scene
{

	map< string, shared_ptr< Geometry > > geometries; 

	b2World world;
	
	float physics_to_graphics_scale = 100.f;
	
	RenderWindow * window;
	
public:
	
	Scene(RenderWindow & window);
		
	Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position)
	{
		return Vector2f(box2d_position.x * physics_to_graphics_scale, window->getSize().y - box2d_position.y * physics_to_graphics_scale);
	}
	
	float get_scale () const;
	
	void run ()
	{
		bool exit = false;
		
		do
		{
			process_events ();
			
			...
			
			window->clear ();
		
			render ();
			
			window->display ();
			
			...
		}
		while (!exit);
	}


private:
	
	void render ()
	{
		for (auto & geometry : geometries)
		{
			geometry.second->render (window);
		}
	}
	
	
	void create_scene ();		// crear todos los elementos de la escena

	void process_events ();


};