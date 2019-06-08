#pragma once
#include <cmath>

struct Particle;

class EntropyCounter
{
public:

    //dummy method to be overwritten later
    float get_entropy() { float rv = sin(time) * 500 + 1000; time += 3.14f / 10; return rv; }

private:
    float time {0};

};