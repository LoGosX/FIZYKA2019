#pragma once
#include <SFML/Graphics/Color.hpp>
#include <cmath>

namespace constants
{
	//Physic constants
	const float PARTICLE_MASS = 1.f;
	const float PARTICLE_RADIUS = 0.1f;
	const float R = 50.f;
	const float W = 100.0f;
	const size_t PARTICLES_COUNT = 50000;
	const float DELTA_TIME = 1.f / (2 * W);
	const float INITIAL_VELOCITY_MODIFIER = 10000.f;
	const size_t CELL_FACTOR = 1;

	//Drawing constants
	const sf::Color PARTICLE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_OUTLINE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_FILL_COLOR = sf::Color::Black;
	const float CONTAINER_OUTLINE_THICKNESS = 1.f;
	const int OK_VERTICES_COUNT = 100000; //how much vertices should we draw (number of particles on screen * number of vertices in particle sprite <= OK_VERTICES_COUNT)

	//Entropy constants
	const int BOX_NUMBER = 5;			// there is BOX_NUMBER^4 possible states

	//Other constants
	const bool DEBUG_LOG = false;
	const float ENTROPY_LOG_DELAY = sqrt(PARTICLES_COUNT) / 200.0;
	const float BARRIER_LIFETIME =  0.f; //1s irl
};
