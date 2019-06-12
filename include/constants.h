#pragma once
#include <SFML/Graphics/Color.hpp>

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
	const size_t CELL_FACTOR = 1.f;

	//Drawing constants
	const sf::Color PARTICLE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_OUTLINE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_FILL_COLOR = sf::Color::Black;
	const float CONTAINER_OUTLINE_THICKNESS = 1.f;
	const int OK_VERTICES_COUNT = 100000; //how much vertices should we draw (number of particles on screen * number of vertices in particle sprite <= OK_VERTICES_COUNT)

	//Other constants
	const bool DEBUG_LOG = true;
	const bool PARALLEL = true; //graphics and physics in separate threads
};
