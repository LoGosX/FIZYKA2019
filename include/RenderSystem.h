#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

struct Particle;

class RenderSystem
{
	/*
	Class responsible for drawing and input handling
	*/
	std::unique_ptr<sf::RenderWindow> window;
	sf::CircleShape particle_sprite;
	sf::RectangleShape container;
	sf::VertexArray va; //used for drawing particles in one draw call
	sf::VertexBuffer vb;

	// If zoom_amount is 1.1f, it will zoom in or out by 10 % ;
	// if zoom_amount is 1.3f, it will zoom in or out by 30 % .
	float zoom_amount{ 1.1f };
	bool mouse_down{ false };
	bool mouse_moved{ false };
	bool window_closed{ false };
	sf::Vector2f last_mouse_global_position, current_mouse_global_position;
	sf::Vector2i last_mouse_local_position, current_mouse_local_position;
	void move_view(); //move view resulting from mouse drag
	int window_width;
	int window_height;
	const char* window_title;
	int updates_count{0}; //incremented whenever window->display is called
public:
	RenderSystem(int window_width, int window_height, const char* window_title);
	~RenderSystem();

	bool is_window_open() const;
	bool draw_particles(const std::vector<Particle>& particles);
	bool draw_particles_container();
	void setup_particle_container(const sf::FloatRect& container);
	bool display();
	bool clear();
	bool handle_input();
	bool initialize(); //initialize OpenGL context through SFML
	int num_of_updates() const;
};

