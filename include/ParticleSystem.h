#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
};

class ParticleSystem
{
	/*
		Class that owns all particles in simulation.
		It is also responsible for all physics: collision handling and position updates
	*/

	const int PARTICLE_COUNT;
	const sf::Vector2f UPPER_LEFT, BOTTOM_RIGHT;
	std::vector<Particle> particles;

	void spawn_particles();
	void update_positions(double delta_time);
	void update_wall_collisions();
	void update_particles_collisions();
public:
	/*
	particle_count - how many particles to spawn
	area_dimensions - width and height of rectangle in which particles are moving. The UPPER_LEFT corner of rectangle is (0, 0), where BOTTOM_RIGHT corner is area_dimensions 
	*/

	static const float PARTICLE_RADIUS; //defined in ParticleSystem.cpp

	ParticleSystem(int particle_count, sf::Vector2f area_dimensions);
	~ParticleSystem();

	bool update(double delta_time); 

	const std::vector<Particle>& get_particles() const;
};

