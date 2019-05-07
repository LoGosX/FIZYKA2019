#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "EntropyCounter.h"


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

	std::unique_ptr<EntropyCounter> _enCounter; // This is my stuff to count a entropy of the system

	void spawn_particles();
	void update_positions(double delta_time);
	void update_wall_collisions();
	void update_particles_collisions();
public:
	/*
	particle_count - how many particles to spawn
	R - 1/2 of width and height of rectangle in which particles are moving. The UPPER_LEFT corner of rectangle is (-R, R), where BOTTOM_RIGHT corner is (R,R)
	Note that Y axis is inverted (Y is getting bigger when moving down)
	*/

	ParticleSystem(int particle_count, float R);
	~ParticleSystem();

	bool update(double delta_time); 

	const std::vector<Particle>& get_particles() const;
};

