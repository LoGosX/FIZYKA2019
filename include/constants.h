#pragma once
#include <SFML/Graphics/Color.hpp>

namespace constants
{
	//Physic constants
	const float PARTICLE_MASS = 1.f;
	const float PARTICLE_RADIUS = 0.1f;
	const float R = 10.f;
	const float W = 300.0f;
	const size_t PARTICLES_COUNT = 2000;
	const float DELTA_TIME = 1.f / (2 * W);
	const float INITIAL_VELOCITY_MODIFIER = 5.f;

	//Drawing constants
	const sf::Color PARTICLE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_OUTLINE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_FILL_COLOR = sf::Color::Black;
	const float CONTAINER_OUTLINE_THICKNESS = 0.1f;

	//Entropy constants
	const int BOX_NUMBER = 5;			// there is BOX_NUMBER^4 possible states

	//Other constants
	const bool DEBUG_LOG = false;
	const bool PARALLEL = true; //graphics and physics in separate threads
};
