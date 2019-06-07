#pragma once
#include <vector>
#include <memory>
#include "EntropyCounter.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

struct Particle;

class ParticleSystem
{
	/*
		Class that owns all particles in simulation.
		It is also responsible for all physics: collision handling and position updates
	*/

	const int PARTICLE_COUNT;
	const sf::Vector2f UPPER_LEFT, BOTTOM_RIGHT;
	std::vector<Particle> particles;
	std::vector<int> particle_indexes; //used to sort particles. Ask M. Falb why

	std::unique_ptr<EntropyCounter> _enCounter; // This is my stuff to count a entropy of the system

	void printVelocitySum();
	void printArrangement();

	void spawn_particles();
	void update_positions(double delta_time);
	void update_wall_collisions();
	void update_particles_collisions();
	int updates_count{0}; //incremented whenever update(...) is called
public:
	/*
	particle_count - how many particles to spawn
	R - 1/2 of width and height of rectangle in which particles are moving. The UPPER_LEFT corner of rectangle is (-R, R), where BOTTOM_RIGHT corner is (R,R)
	Note that Y axis is inverted (Y is getting bigger when moving down)
	*/

	ParticleSystem(int particle_count, float R);
	~ParticleSystem();

	int num_of_updates() const;

	bool update(double delta_time); 

	const std::vector<Particle>& get_particles() const;

	sf::FloatRect get_container_rect() const;
};

