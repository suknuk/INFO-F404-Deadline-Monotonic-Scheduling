#include <iostream>
#include <cstdlib>
#include <ctime>
#include "random_system.h"

void RandomSystem::generate_system()
{
	std::srand(std::time(0));
	// create a random period between 10 and 100
	int max_period = std::rand() % 90 + 10;
	std::cout << max_period << std::endl;
}

RandomSystem::RandomSystem(int tasks, int utilization)
{
	this->_tasks = tasks;
	this->_utilization = utilization;
	generate_system();
}

