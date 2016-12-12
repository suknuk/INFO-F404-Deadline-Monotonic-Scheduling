#include <iostream>
#include <cstdlib>
#include <ctime>
#include "usefull_methods.h"
#include "random_system.h"

void RandomSystem::generate_system()
{
	std::srand(std::time(0));
	// create a random max_Period between 9 + #tasks*2  and 100 
	int max_period = std::rand() % (41 - this->_tasks*2 )  + ( 9 + this->_tasks*2) ;
	std::cout << "Max period = " << max_period << std::endl;

	std::vector<double> utilization;
	double total_generated_utilization = 0;
	
	// generate n-tasks random utilization factors
	for (int i = 0; i < this->_tasks; i++) {
		double rnd_utilization = std::rand() % 99 + 1;// between 1 and 100
		utilization.push_back( rnd_utilization ); 
		total_generated_utilization += rnd_utilization;
		// std::cout << i << ": " << utilization[i] << std::endl;
	}

	// now make the generated total utilization equal to the target utilization
	for (int i = 0; i < this->_tasks; i++) {
		utilization[i] = (utilization[i] / total_generated_utilization) * this->_utilization;
		// std::cout << i << ": " << utilization[i] << std::endl;
	}

	// carry value that takes over the utilization factor that was over or under achieved by 
	// the previous tasks
	double utilization_carry = 0;

	//std::vector<Task> tasks;
	// find values that try to match the utilization given by the generated utilization value
	for (int i = 0; i < this->_tasks; i++) {
		
		int offset = std::rand() % (max_period/2);

		int best_wcet = 1;
		int best_period = 1;
		double best_carry = 0;
		double lowest_diff = 101; // 101% is the worst value possible

		// iterate every deadline
		for (int period = 1; period <= max_period; period++) {
			// iterate every period
			for (int wcet = 1; wcet <= period; wcet++) {
				// what is the utilization of these values?
				double tmp_u = (double(wcet)/double(period)) * 100;
			
				// add the Utilization carry so we can get closer the the wanted result
				double diff = utilization[i] + utilization_carry - tmp_u;
				// cast positive if negative
				if (diff < 0) {
					diff = diff * -1; 
				}

				// new best match?
				if (diff < lowest_diff) {
					best_wcet = wcet;
					best_period = period;
					lowest_diff = diff;
					best_carry = utilization[i] + utilization_carry - tmp_u ;
				} 
			}
		}

		// take over the best carry value
		utilization_carry = best_carry;

		// get a deadline between wcet and the period
		int deadline;
		
		// case when Utilization is at 100%
		if (best_period == best_wcet) {
			deadline = best_period;
		} else {
			deadline = std::rand() % (best_period - best_wcet) + best_wcet;
		}

		/*
		double reached_diff = (double(best_wcet)/double(best_period)) * 100;

		std::cout << "offset : " << offset << ", period: " << best_period
			<< ", deadline: " << deadline << ", wcet: " << best_wcet
			<< ", target U: " << utilization[i]
			<< ", reached U: " << reached_diff
			<< std::endl;
		*/

		Task task(offset, best_period, deadline, best_wcet);
		this->_tasks_vector.push_back(task);
	}
	// TODO When the carry value is too big, go back to the list and look where we can increase
	// the Utilization of single tasks to make it closer to the wanted value
	std::cout << "U carry: " << utilization_carry << std::endl;

}

RandomSystem::RandomSystem(int tasks, int utilization)
{
	this->_tasks = tasks;
	this->_utilization = utilization;
	generate_system();
}

std::vector<Task> RandomSystem::get_tasks()
{
	return this->_tasks_vector;
}
