#include <iostream>

#include "ParticleSystem.h"
#include "constants.h"
#include "Particle.h"
#include "utils.h"

ParticleSystem::ParticleSystem(int particle_count, float R) : PARTICLE_COUNT(particle_count), UPPER_LEFT(sf::Vector2f{ -R, -R }), BOTTOM_RIGHT(sf::Vector2f{ R, R }), cell_size(2 * constants::PARTICLE_RADIUS * constants::CELL_FACTOR)
{
	size_t width = BOTTOM_RIGHT.x - UPPER_LEFT.x,
		height = BOTTOM_RIGHT.y - UPPER_LEFT.y;
	particle_cells.resize(width / cell_size + 1);
	for (int i =0;i<particle_cells.size();i++)
		particle_cells[i].resize(height / cell_size + 1);

	_enCounter = std::make_unique<EntropyCounter>();
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
		float x = utils::random::rand(-constants::R, -0.25f * constants::R);
		float y = utils::random::rand(-constants::R, constants::R);

		particles.emplace_back(Particle{ sf::Vector2f{ x, y }, sf::Vector2f{ vx, vy } * constants::INITIAL_VELOCITY_MODIFIER });
	}
}

void ParticleSystem::update_positions(double delta_time)
{
	for (auto& p : particles)
		p.position += p.velocity * (float)delta_time;
}

void ParticleSystem::printVelocitySum()
{
	double sum = 0;
	for (auto p : particles)
	{
		sum += p.velocity.x*p.velocity.x + p.velocity.y* p.velocity.y;
	}
	std::cerr << sum << "\n";
}

void ParticleSystem::printArrangement()
{
	long long left = 0, right = 0;
	for (auto p : particles)
	{
		if (p.position.x <= 0)
			left++;
		else
			right++;
	}
	std::cerr << left << " : " << right << "\n";
}

void particlesCollide(Particle& a, Particle& b)
{
	sf::Vector2f L = b.position - a.position;
	float distanceSquared = L.x*L.x + L.y * L.y;
	if (distanceSquared <= 4 * constants::PARTICLE_RADIUS*constants::PARTICLE_RADIUS) //in range
	{
		sf::Vector2f FirstParallel = (a.velocity.x * L.x + a.velocity.y * L.y) / distanceSquared * L,
			SecondParallel = (b.velocity.x * L.x + b.velocity.y * L.y) / distanceSquared * L,
			FirstPerpendicular = a.velocity - FirstParallel,
			SecondPerpendicular = b.velocity - SecondParallel;
		if ((SecondParallel - FirstParallel).x * L.x < 0 || (SecondParallel - FirstParallel).y * L.y < 0) //collision
		{
			a.velocity = FirstPerpendicular + SecondParallel;
			b.velocity = SecondPerpendicular + FirstParallel;
		}
	}
}

void ParticleSystem::update_particles_collisions()
{
	float PARTICLE_RADIUS = constants::PARTICLE_RADIUS;

	for (int i = 0; i < particle_cells.size(); i++)
		for (int j = 0; j < particle_cells[i].size(); j++)
			particle_cells[i][j].clear();

	for (int i = 0; i < particles.size(); i++)
		particle_cells[(particles[i].position.x - UPPER_LEFT.x) / cell_size][(BOTTOM_RIGHT.y - particles[i].position.y) / cell_size].push_back(i);

	for(int i=0;i<particle_cells.size();i++)
		for (int j = 0; j< particle_cells[i].size(); j++)
			for (auto index1 : particle_cells[i][j])
			{
				Particle &a = particles[index1];
				sf::Vector2i moves[] = { {0,0}, {1,0}, {0,1}, {1,1}, {1,-1} };
				for (auto move : moves)
					if( (i + move.x)>=0 && (j + move.y) >= 0 && (i + move.x) < particle_cells.size() && (j + move.y) < particle_cells[i + move.x].size())
						for (auto index2 : particle_cells[i + move.x][j + move.y])
						{
							Particle &b = particles[index2];
							particlesCollide(a, b);
						}
			}

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