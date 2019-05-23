#pragma once
#include <SFML/Graphics/Color.hpp>

namespace constants
{
	//Physic constants
	const float PARTICLE_MASS = 1.f;
	const float PARTICLE_RADIUS = 0.1f;
	const float R = 20.f;
	const float W = 100.0f;
	const size_t PARTICLES_COUNT = 50000;
	const float DELTA_TIME = 1.f / (2 * W);
	const float INITIAL_VELOCITY_MODIFIER = 100.f;

	//Drawing constants
	const sf::Color PARTICLE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_OUTLINE_COLOR = sf::Color::Red;
	const sf::Color CONTAINER_FILL_COLOR = sf::Color::Black;
	const float CONTAINER_OUTLINE_THICKNESS = 1.f;
};
