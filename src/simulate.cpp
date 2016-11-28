#include <string>
#include "usefull_methods.h"
#include <iostream>
#include <cmath>
#include "simulate.h"

void simulate_global(std::vector<Task> &tasks, int processors)
{
	// #processors enough for total utilisation?
	double utilization = total_utilization(tasks);
	int utilization_int = ceil(utilization);

	std::cout << "Total utilization of the system is " << utilization << std::endl;
	
	// System can not be scheduled with the #processors
	if (utilization > (double)processors) {
		std::cout << "System is unable to be scheduled on this system. For"
			<< " the simulation of the system, we require at least " 
			<< utilization_int << " processors instead of " << processors
			<< std::endl;
		return;
	}

	int study_interval = interval(tasks);
	std::cout << "Simulating over the interval of " << study_interval << std::endl;
	
	// vector of vectors to hold the scheduling of the system
	std::vector< std::vector<Task *> > schedule;
	
	// create n processor vectors which represent 1 processor each
	for (int i = 0; i < processors; i++) {
		schedule.push_back(std::vector<Task *>());
		for (int j = 0; j < study_interval; j++) {
			schedule[i].push_back(NULL);	
		}
	}

	// Iterating every task by priority 
	for (unsigned i = 0; i < tasks.size(); i++) {
		// Iterating every period of the task starting at the offset
		for (int position = tasks[i].get_offset(); 
			position < study_interval;
			position += tasks[i].get_period())
		{
			// Position by which the current task has to be finished
			int has_to_finish_at = position + tasks[i].get_deadline();
			// How many slots we have to fill in the period
			int wcet_to_fill = tasks[i].get_wcet();
			
			// Fill the processors from the left
			for (int left = position; left < has_to_finish_at; left++){
				for (scheduler_y = 0; scheduler_y < schedule.size(); scheduler_y++) {
					// find emtpy slot

					// TODO improvement? continue using the same processor to fill up
					// places rather than looking from the top
				}
			}
		}
	}

}





