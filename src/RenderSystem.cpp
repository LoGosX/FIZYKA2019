#include <cstdlib> // for srand()

#include <SFML/Graphics.hpp>
#include "RenderSystem.h"
#include "Particle.h"
#include "constants.h"
#include "ParticleSystem.h"

RenderSystem::RenderSystem(int window_width, int window_height, const char* window_title)
{
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_width, window_height), window_title));
	particle_sprite = sf::CircleShape(constants::PARTICLE_RADIUS);
	particle_sprite.setFillColor(sf::Color::Green);
	particle_sprite.setOrigin(constants::PARTICLE_RADIUS, constants::PARTICLE_RADIUS);
	sf::View view;
	view.setCenter(0, 0);
	view.setSize(2 * constants::R, 2 * constants::R);
	window->setView(view);

	srand(0); //constant seed to get reproducible simulations
}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::is_window_open() const
{
	return window->isOpen();
}

bool RenderSystem::draw_particles(const std::vector<Particle>& particles)
{
	for (auto& p : particles)
	{
		particle_sprite.setPosition(p.position);
		window->draw(particle_sprite);
	}
	return true;
}

bool RenderSystem::display()
{
	window->display();
	return true;
}

bool RenderSystem::clear()
{
	window->clear();
	return true;
}

bool RenderSystem::handle_input()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
	return true;
}
