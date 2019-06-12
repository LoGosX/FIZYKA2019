#include "EntropyCounter.h"

EntropyCounter::EntropyCounter()
{
	EntropyCounter(sf::Rect<float>{0,0,0,0}, 0, 1);
}

EntropyCounter::EntropyCounter(const sf::Rect<float> & newArea, float maxSpeed, int pred)
{
	_areaSize = newArea;
	_maxSpeed = maxSpeed;
	_boxNumber = pred;
}

void EntropyCounter::setArea(const sf::Rect<float> & newArea)
{
	_areaSize = newArea;
}

void EntropyCounter::setArea(float x, float y, float w, float h)
{
	this->setArea(sf::Rect<float>{x,y,w,h});
}

void EntropyCounter::setMaxSpeed(float speed)
{
	_maxSpeed = speed;
}

void EntropyCounter::setPreccision(int pred)
{
	_boxNumber = pred;
}

float EntropyCounter::get_entropy(const std::vector<Particle> & particles)const
{
	return _entropy;
}

float EntropyCounter::get_probability(const std::vector<Particle> & particles)const
{
	return _probability;
}

const std::vector<int> & EntropyCounter::getNumberOfParticlesInStates()const
{
	return _numberInStates;
}

void EntropyCounter::updateEntropy(const std::vector<Particle> & particles)
{
	auto states = this->getStates(particles);
	_numberInStates = this->calculateStateNumber(states);
	auto N = particles.size();
	_entropy = (N * log(N) - N);
	for(auto x: _numberInStates)
		_entropy -=(x * log(x) -x);
}

std::vector<ParticleState> EntropyCounter::getStates(const std::vector<Particle> & particles)
{

	
