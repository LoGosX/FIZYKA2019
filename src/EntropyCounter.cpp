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

float EntropyCounter::get_entropy()
{
	return _entropy;
}

float EntropyCounter::get_probability()
{
	return _probability;
}

const std::vector<int>& EntropyCounter::getNumberOfParticlesInStates()
{
	return _numberInStates;
}

void EntropyCounter::updateEntropy(const std::vector<Particle> & particles)
{
	auto states = this->getStates(particles);
	_numberInStates = this->calculateStateNumber(states);
	auto N = particles.size();
	_entropy = ln_factorial(N);
	for(auto x: _numberInStates)
		if(x!= 0)
			_entropy -=ln_factorial(x);

	_probability = exp(_entropy);
}

std::vector<EntropyCounter::ParticleState> EntropyCounter::getStates(const std::vector<Particle>& particles)
{
	auto res = std::vector<ParticleState>{};
	for (const auto & p: particles)
	{
		if (p.velocity.x > _maxSpeed || p.velocity.y > _maxSpeed || p.velocity.x < - _maxSpeed || p.velocity.y < -_maxSpeed)
			continue;

		int x = (p.position.x - _areaSize.left)*_boxNumber / _areaSize.width;
		int y = (p.position.y - _areaSize.top)*_boxNumber / _areaSize.height;

		int vx = (p.velocity.x + _maxSpeed)*_boxNumber / (2*_maxSpeed);
		int vy = (p.velocity.y + _maxSpeed)*_boxNumber / (2*_maxSpeed);

		res.push_back({ x,y,vx,vy });
	}
	return res;
}

std::vector<int> EntropyCounter::calculateStateNumber(const std::vector<ParticleState>& states)
{
	auto res = std::vector<int>{};
	res.resize(_boxNumber*_boxNumber*_boxNumber*_boxNumber);
	for (const auto & s: states)
	{
		auto index = s.posX + s.posY*_boxNumber + s.velX * _boxNumber*_boxNumber + s.velY * _boxNumber*_boxNumber*_boxNumber;
		res[index]++;
	}
	return res;
}

	
