#include <iostream>

#include <SFML/Graphics.hpp>
#include "RenderSystem.h"
#include "Particle.h"
#include "constants.h"
#include "ParticleSystem.h"
#include "utils.h"


RenderSystem::RenderSystem(int window_width, int window_height, const char* window_title) : window_width(window_width), window_height(window_height), window_title(window_title)
{
}

bool RenderSystem::initialize()
{
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_width, window_height), window_title, sf::Style::Close)); //sf::Style::Close until resizing is properly handled
	//set particle sprite
	particle_sprite = sf::CircleShape(constants::PARTICLE_RADIUS);
	particle_sprite.setFillColor(constants::PARTICLE_COLOR);
	particle_sprite.setOrigin(constants::PARTICLE_RADIUS, constants::PARTICLE_RADIUS);
	sf::View view;
	view.setCenter(0, 0);
	view.setSize(2 * constants::R, 2 * constants::R);
	window->setView(view);

	//window->setVerticalSyncEnabled(true);
	return true;
}

RenderSystem::~RenderSystem()
{
}

bool RenderSystem::is_window_open() const
{
	return !window_closed;
}

bool RenderSystem::draw_particles(const std::vector<Particle>& particles)
{
	sf::FloatRect rect{ window->getView().getCenter() - window->getView().getSize() / 2.f, window->getView().getSize() };
	sf::VertexArray va(sf::PrimitiveType::Triangles);
	int pc = particle_sprite.getPointCount();
	va.resize(particles.size() + 3 * particles.size() * pc);
	int k = 0;
	const sf::Vector2f t{constants::PARTICLE_RADIUS, constants::PARTICLE_RADIUS};
	for(auto/*&*/ p : particles)
	{
		sf::FloatRect r {p.position - t, t * 2.f};
		if(!rect.intersects(r))
			continue;
		sf::Vertex v;
		float max_vel = constants::W / (2 * constants::PARTICLES_COUNT) * constants::INITIAL_VELOCITY_MODIFIER;
		auto fraction = utils::dot(p.velocity, p.velocity) / (4 * max_vel * max_vel);
		int R = 255 * fraction;
		int B = -255 * fraction + 255;
		int G = 0;
		R = std::max(0, R);
		R = std::min(255, R);
		B = std::max(0, B);
		B = std::min(255, B);
		v.color = sf::Color(R, G, B);
		for(int i = 0; i < pc - 1; i++)
		{
			v.position = particle_sprite.getPoint(i) + p.position - t;
			va[k++] = v;
			v.position = particle_sprite.getPoint(i + 1) + p.position - t;
			va[k++] = v;
			v.position = p.position;
			va[k++] = v;
		}
		v.position = particle_sprite.getPoint(pc - 1) + p.position - t;
		va[k++] = v;
		v.position = particle_sprite.getPoint(0) + p.position - t;
		va[k++] = v;
		v.position = p.position;
		va[k++] = v;
	}
	va.resize(k);
	window->draw(va);
	return true;
}

void RenderSystem::setup_particle_container(const sf::FloatRect& container)
{
	//set container rectangle
	auto& rect = this->container;
	sf::Vector2f upper_left{ container.left, container.top };
	sf::Vector2f size{ container.width, container.height };
	rect.setSize(size);
	rect.setOrigin(size / 2.f);
	rect.setOutlineColor(constants::CONTAINER_OUTLINE_COLOR);
	rect.setOutlineThickness(constants::CONTAINER_OUTLINE_THICKNESS);
	rect.setFillColor(constants::CONTAINER_FILL_COLOR);
}

bool RenderSystem::draw_particles_container()
{
	window->draw(container);

	return true;
}


bool RenderSystem::display()
{
	updates_count++;
	window->display();
	return true;
}

bool RenderSystem::clear()
{
	window->clear();
	return true;
}

int RenderSystem::num_of_updates() const{ return updates_count; }

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	sf::View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
}

bool RenderSystem::handle_input()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			window_closed = true;
		}
		
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			//TODO: update the view to the new size of the window
		}

		if (event.type == sf::Event::MouseMoved)
		{
			mouse_moved = true;
			if (mouse_down)
			{
				last_mouse_global_position = current_mouse_global_position;
				current_mouse_global_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

				last_mouse_local_position = current_mouse_local_position;
				current_mouse_local_position = sf::Mouse::getPosition(*window);
			}
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
				zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *window, (1.f / zoom_amount));
			else if (event.mouseWheelScroll.delta < 0)
				zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *window, zoom_amount);
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouse_down = true;
				last_mouse_global_position = current_mouse_global_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

				last_mouse_local_position = current_mouse_local_position = sf::Mouse::getPosition(*window);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				mouse_down = false;
		}
	}

	//drag screen with mouse 
	if (mouse_moved && mouse_down)
	{
		//sf::Vector2f offset = last_mouse_global_position - current_mouse_global_position;
		
		sf::Vector2f offset = window->mapPixelToCoords(last_mouse_local_position) - window->mapPixelToCoords(current_mouse_local_position);
		sf::View new_view = window->getView();
		new_view.move(offset);
		window->setView(new_view);
	}

	mouse_moved = false;
	return true;
}
