#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

struct Particle;

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
	EntropyCounter(sf::Rect<float> & newArea, float maxSpeed, int pred);


	//
	
	void setArea(const sf::Rect<float> & newArea);
	void setArea(float x, float y, float w, float h);

	void setMaxSpeed(float speed);

	void setPreccision(int prec);		// sets how many boxes is created

	//

    	float get_entropy(const std::vector<Particle> & particles);
    	float get_probability(const std::vector<Particle> & particles);
       

private:
    	
    	float _maxSpeed;
	float _boxNumber;
	sf::Rect<float> AreaSize;
	
	float entropy;
	float probability;

private:
	
	void updateEntropy(const std::vector<Particle> & particles);
	void updateProbability(const std::vector<Particle> & particles);
	
	std::vector<ParticleState> getStates(const std::vector<Particle> & particles);
	std::vector<int> calculateStateNumber(const std::vector<ParticleState> & states);


};
