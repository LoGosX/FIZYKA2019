#include "RenderSystem.h"
#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

RenderSystem::RenderSystem(int window_width, int window_height, const char* window_title)
{
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_width, window_height), window_title));
	particle_sprite = sf::CircleShape(ParticleSystem::PARTICLE_RADIUS);
	particle_sprite.setFillColor(sf::Color::Red);
	particle_sprite.setOrigin(ParticleSystem::PARTICLE_RADIUS, ParticleSystem::PARTICLE_RADIUS);
	particle_sprite.setOutlineColor(sf::Color::Green);
	particle_sprite.setOutlineThickness(2);
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
