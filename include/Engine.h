#pragma once
#include <memory>
#include <chrono> //high precision time measuring

class RenderSystem;
class ParticleSystem;

class Engine
{
	std::unique_ptr<RenderSystem> render_system;
	std::unique_ptr<ParticleSystem> particle_system;
	bool is_running{ false };
public:
	Engine(int window_width, int window_height, const char* window_title);
	~Engine();

	void run();

	//delta_time is in seconds
	bool update(double delta_time);

	bool draw();
};

