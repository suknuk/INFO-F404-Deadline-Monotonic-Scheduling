#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "random_system.h"

void RandomSystem::generate_system()
{
	std::srand(std::time(0));
	// create a random max_Period between 10 and 100
	int max_period = std::rand() % 90 + 10;
	std::cout << "Max period = " << max_period << std::endl;
	
	// holds all tasks
	//std::vector<Task> schedule;
	for (int i = 0; i < this->_tasks; i++) {
		
		int offset = std::rand() % (max_period/2);
		
		int period = std::rand() % max_period + 10;

		// has to be at least 1
		int wcet = std::rand() % (max_period-1) + 1;

		int deadline = std::rand() % (period - wcet) + wcet;

		std::cout << "offset : " << offset << ", period: " << period
			<< ", deadline: " << deadline << ", wcet: " << wcet
			<< std::endl;

		//Task task
	}

}

RandomSystem::RandomSystem(int tasks, int utilization)
{
	this->_tasks = tasks;
	this->_utilization = utilization;
	generate_system();
}

