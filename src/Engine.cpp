#include <iostream>

#include "Engine.h"
#include "RenderSystem.h"
#include "ParticleSystem.h"
#include "constants.h"

Engine::Engine(int window_width, int window_height, const char * window_title)
{
	std::cout << "Initializing systems.\n";
	
	//window has a shape of square until window resizing is not handled properly
	if (window_height > window_width)
		window_width = window_height;
	if (window_width > window_height)
		window_height = window_width;

	render_system = std::unique_ptr<RenderSystem>(new RenderSystem(window_width, window_height, window_title));
	particle_system = std::unique_ptr<ParticleSystem>(new ParticleSystem(constants::PARTICLES_COUNT, constants::R)); //TODO: load values from file (?)

	render_system->setup_particle_container(particle_system->get_container_rect());
}

Engine::~Engine()
{
}

void Engine::run()
{
	std::cout << "Running engine.\n";
	is_running = true;
	auto start = std::chrono::high_resolution_clock::now();
	while (is_running)
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> delta_time(now - start);
		start = now;
		bool result = update(delta_time.count());
		if (!result)
		{
			std::cout << "Engine::update() failure. Aborting.\n";
			is_running = false;
			break;
		}

		result = draw();

		if (!result)
		{
			std::cout << "Engine::draw() failure. Aborting.\n";
			is_running = false;
			break;
		}

		if (!render_system->is_window_open())
			is_running = false;
	}
	std::cout << "Engine stopped.\n";
}

bool Engine::update(double delta_time)
{
	particle_system->update(delta_time);
	render_system->handle_input();
	return true;
}

bool Engine::draw()
{
	render_system->clear();
	render_system->draw_particles_container();
	render_system->draw_particles(particle_system->get_particles());
	render_system->display();

	return true;
}
