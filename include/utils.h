#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>
#include <iostream>

namespace utils
{
	float sqr_magnitude(const sf::Vector2f& a) { return a.x * a.x + a.y * a.y; }
	float magnitude(const sf::Vector2f& a) { return sqrtf(sqr_magnitude(a)); }
	float sqr_distance(const sf::Vector2f& a, const sf::Vector2f& b) { return sqr_magnitude(a - b); }
	float distance(const sf::Vector2f& a, const sf::Vector2f& b) { return sqrtf(sqr_distance(a, b)); }
	
	template<typename T>
	float dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b){ return a.x * b.x + a.y * b.y;}
	
	sf::Vector2f normalize(const sf::Vector2f& a){ return a / magnitude(a); }

	
	namespace random
	{
		std::mt19937 _mt;
		std::uniform_real_distribution<float> _dist(0.f, 1.f);

		//returns a random float number from range [a, b]. Default range is [0, 1]
		float rand(float a = 0.f, float b = 1.f) { return _dist(_mt) * (b - a) + a; }
		//returns a random integer value from range [a, b]
		int randint(int a, int b) { return (int)((_dist(_mt)) * (b - a) + a + .5f); }
	}
};