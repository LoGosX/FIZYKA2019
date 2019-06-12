
#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

namespace utils
{
	template<typename T>
	inline float dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b){ return a.x * b.x + a.y * b.y;}

	inline float sqr_magnitude(const sf::Vector2f& a) { return dot(a, a); }
	inline float magnitude(const sf::Vector2f& a) { return sqrtf(sqr_magnitude(a)); }
	inline float sqr_distance(const sf::Vector2f& a, const sf::Vector2f& b) { return sqr_magnitude(a - b); }
	inline float distance(const sf::Vector2f& a, const sf::Vector2f& b) { return sqrtf(sqr_distance(a, b)); }
	
	inline sf::Vector2f normalize(const sf::Vector2f& a){ return a / magnitude(a); }

	template<typename A, typename B, typename C>
	inline typename std::common_type<A, B, C>::type clamp(A val, B min, C max) { return (val < min ? min : (val > max ? max : val)); }

	namespace random
	{
		inline static std::mt19937 _mt;
		inline static std::uniform_real_distribution<float> _dist(0.f, 1.f);

		//returns a random float number from range [a, b]. Default range is [0, 1]
		inline float rand(float a = 0.f, float b = 1.f) { return _dist(_mt) * (b - a) + a; }
		//returns a random integer value from range [a, b]
		inline int randint(int a, int b) { return (int)((_dist(_mt)) * (b - a) + a + .5f); }
	}
};