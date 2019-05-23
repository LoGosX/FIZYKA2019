#include "Engine.h"

int main()
{
	Engine* engine = new Engine(1600, 1600, "FIZYKA?");

	engine->run();

	delete engine;

	return 0;
}