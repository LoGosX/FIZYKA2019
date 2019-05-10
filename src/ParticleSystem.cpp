#include <iostream>

#include "ParticleSystem.h"
#include "constants.h"
#include "Particle.h"
#include "utils.h"

ParticleSystem::ParticleSystem(int particle_count, float R) : PARTICLE_COUNT(particle_count), UPPER_LEFT(sf::Vector2f{ -R, -R }), BOTTOM_RIGHT(sf::Vector2f{ R, R })
{
	spawn_particles();
}

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::update(double delta_time)
{
	update_positions(delta_time);
	update_wall_collisions();
	update_particles_collisions();
	return true;
}

void ParticleSystem::spawn_particles()
{
	float max_vel = constants::W / (2 * PARTICLE_COUNT);
	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		float vx = utils::random::rand(-max_vel, max_vel);
		float vy = utils::random::rand(-max_vel, max_vel);
		float x = utils::random::rand(-constants::R, constants::R);
		float y = utils::random::rand(-constants::R, constants::R);
		particles.emplace_back(Particle{ sf::Vector2f{ x, y }, sf::Vector2f{ vx, vy } });
	}
}

void ParticleSystem::update_positions(double delta_time)
{
	for (auto& p : particles)
		p.position += p.velocity * (float)delta_time;
}

void ParticleSystem::update_particles_collisions()
{
	//TODO
}

void ParticleSystem::update_wall_collisions()
{
	//wall collisions
	float PARTICLE_RADIUS = constants::PARTICLE_RADIUS;
	for (auto& p : particles)
	{
		if (p.position.x - PARTICLE_RADIUS <= UPPER_LEFT.x)
		{
			p.position.x = UPPER_LEFT.x + PARTICLE_RADIUS;
			p.velocity.x *= -1;
		}
		if (p.position.x + PARTICLE_RADIUS >= BOTTOM_RIGHT.x)
		{
			p.position.x = BOTTOM_RIGHT.x - PARTICLE_RADIUS;
			p.velocity.x *= -1;
		}
		if (p.position.y - PARTICLE_RADIUS <= UPPER_LEFT.y)
		{
			p.position.y = UPPER_LEFT.y + PARTICLE_RADIUS;
			p.velocity.y *= -1;
		}
		if (p.position.y + PARTICLE_RADIUS >= BOTTOM_RIGHT.y)
		{
			p.position.y = BOTTOM_RIGHT.y - PARTICLE_RADIUS;
			p.velocity.y *= -1;
		}
	}
}

const std::vector<Particle>& ParticleSystem::get_particles() const
{
	return particles;
}

sf::FloatRect ParticleSystem::get_container_rect() const
{
	return sf::FloatRect{ UPPER_LEFT, BOTTOM_RIGHT - UPPER_LEFT };
}