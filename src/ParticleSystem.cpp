#include "ParticleSystem.h"
#include <iostream>

const float ParticleSystem::PARTICLE_RADIUS = 50.f;

ParticleSystem::ParticleSystem(int particle_count, sf::Vector2f area_dimensions) : PARTICLE_COUNT(particle_count), UPPER_LEFT(sf::Vector2f{ 0.0f, 0.0f }), BOTTOM_RIGHT(area_dimensions)
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
	for(int i = 0; i < PARTICLE_COUNT; i++)
		particles.emplace_back(Particle{(BOTTOM_RIGHT - UPPER_LEFT) / 2.f, { 400.f / (i + 1), 444.f / (i + 1) }});
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
