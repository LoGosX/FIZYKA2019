#pragma once
#include <SFML/Graphics/Color.hpp>

namespace constants
{
	//Physic constants
	const float PARTICLE_MASS = 1.f;
	const float PARTICLE_RADIUS = 0.1f;
	const float R = 10.f;
	const float W = 10000.f;
	const size_t PARTICLES_COUNT = 1000;
	const float DELTA_TIME = 1.f / (2 * W);

	//Drawing constants
	const sf::Color PARTICLE_COLOR = sf::Color::Green;
	const sf::Color CONTAINER_OUTLINE_COLOR = sf::Color::Red;
	const sf::Color CONTAINER_FILL_COLOR = sf::Color::Black;
	const float CONTAINER_OUTLINE_THICKNESS = .1f;
};
