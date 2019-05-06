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
public:
	RenderSystem(int window_width, int window_height, const char* window_title);
	~RenderSystem();

	bool is_window_open() const;
	bool draw_particles(const std::vector<Particle>& particles);
	bool display();
	bool clear();
	bool handle_input();
};

