#include "Engine.h"

int main()
{
	Engine* engine = new Engine(800, 600, "FIZYKA?");

	engine->run();

	delete engine;

	return 0;
}