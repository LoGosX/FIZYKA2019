#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Particle.h"

class EntropyCounter
{
public:

	struct ParticleState
	{
		int posX;
		int posY;
		int velX;
		int velY;
	};
	
	EntropyCounter();
	EntropyCounter(const sf::Rect<float> & newArea, float maxSpeed, int pred);


	//
	
	void setArea(const sf::Rect<float> & newArea);
	void setArea(float x, float y, float w, float h);

	void setMaxSpeed(float speed);

	void setPreccision(int prec);		// sets how many boxes is created

	//

    float get_entropy();
    float get_probability();
	const std::vector<int> & getNumberOfParticlesInStates();
	void updateEntropy(const std::vector<Particle> & particles);

private:
    	
    float _maxSpeed;
	float _boxNumber;
	sf::Rect<float> _areaSize;
	
	float _entropy;
	float _probability;
	std::vector<int> _numberInStates;
private:

	
	std::vector<ParticleState> getStates(const std::vector<Particle> & particles);
	std::vector<int> calculateStateNumber(const std::vector<ParticleState> & states);

	float ln_factorial(unsigned int n)
	{
		float ret = log(1);
		for (unsigned int i = 1; i <= n; ++i)
			ret += log(i);
		return ret;
	}


};
