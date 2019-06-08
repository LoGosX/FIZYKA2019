#include "Engine.h"
#include <string>
#include <iostream>

int main(int argc, char ** args)
{
	int width = 800, height = 800;
	if(argc == 3)
	{
		try
		{
			width = std::stoi(args[1]);
			height = std::stoi(args[2]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	Engine* engine = new Engine(width, height, "FIZYKA?");
	try
	{
		std::cerr << "Running engine" << std::endl; 
		engine->run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	

	delete engine;

	return 0;
}