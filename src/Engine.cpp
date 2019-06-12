#include <iostream>

#include "Engine.h"
#include "RenderSystem.h"
#include "ParticleSystem.h"
#include "constants.h"
#include <ctime>

Engine::Engine(int window_width, int window_height, const char * window_title)
{
	std::cerr << window_height << ' ' << window_width << '\n';
	//window has a shape of square until window resizing is not handled properly
	if (window_height > window_width)
		window_width = window_height;
	if (window_width > window_height)
		window_height = window_width;

	render_system = std::unique_ptr<RenderSystem>(new RenderSystem(window_width, window_height, window_title));
	particle_system = std::unique_ptr<ParticleSystem>(new ParticleSystem(constants::PARTICLES_COUNT, constants::R)); //TODO: load values from file (?)


}

Engine::~Engine()
{
}

void Engine::run()
{
	if(!constants::PARALLEL)
	{
		render_system->initialize();
		std::cerr << "Running engine.\n";
		auto duration_cast = [](auto t){ return std::chrono::duration_cast<std::chrono::milliseconds>(t).count(); };
		size_t frame = 1;
		while (running)
		{	
			auto time_point1 = std::chrono::high_resolution_clock::now();
	 		bool result = update(constants::DELTA_TIME);
	 		if (!result)
	 		{
	 			std::cerr << "Engine::update() failure. Aborting.\n";
	 			running = false;
	 			break;
			}
			auto time_point2 = std::chrono::high_resolution_clock::now();
			result = draw();
			if (!result)
			{
				std::cerr << "Engine::draw() failure. Aborting.\n";
				running = false;
				break;
			}
			auto time_point3 = std::chrono::high_resolution_clock::now();
			if(constants::DEBUG_LOG){
				std::printf("Frame %d\n", frame++);
				std::printf("PhysicSystem::update() - %8d ms\n",   duration_cast(time_point2 - time_point1));
				std::printf("RenderSystem::draw()   - %8d ms\n", duration_cast(time_point3 - time_point2));
				std::printf("Total frame time       - %8d ms\n\n", duration_cast(time_point3 - time_point1));
				std::cerr << std::flush;
			}
			if (!render_system->is_window_open())
			{
				std::cerr << "Window closed\n";
				running = false;
			}
		}
	}else
	{
		std::cerr << "Initializing systems.\n";
		std::cerr << "Simulation for " << constants::PARTICLES_COUNT << " particles, gathering entropy data once every " << sqrt(constants::PARTICLES_COUNT) / 50 << " real time seconds.\n";
		render_thread = std::thread([this]{
			std::cerr << "Initializing render_thread\n";
			this->render_system->initialize();
			std::cerr << "Render_thread initialized\n";
			while(this->running)
			{
				this->render_system->handle_input();
				if(!this->render_system->is_window_open())
				{
					this->running = false;
					break;
				}

				this->render_system->clear();
				this->render_system->draw_particles_container();
				this->render_system->draw_particles(this->particle_system->get_particles());
				this->render_system->display();
				}
		});


		std::cerr << "Starting physic_thread\n";
		physic_thread = std::thread([this]{
			while(this->running)
			{
				this->particle_system->update(constants::DELTA_TIME);
			}
		});
		
		std::cerr << "Threads started.\n";
		
		auto entropy_log_thread = std::thread([this]{
			float entropy_delay = sqrt(constants::PARTICLES_COUNT) / 50;
			while(this->running)
			{
				particle_system->get_entropy_counter()->updateEntropy(particle_system->get_particles());
				std::cout << particle_system->get_entropy_counter()->get_entropy() << std::endl;
				sf::sleep(sf::seconds(entropy_delay));
			}
		});
		
		entropy_log_thread.join();
		render_thread.join();
		physic_thread.join();
		std::cerr << "Threads joined\n";
	}
	std::cerr << "Engine stopped.\n";
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
