#include <string>
#include "usefull_methods.h"
#include <iostream>
#include <cmath>
#include "simulate.h"

void initialize_global_schedule(std::vector< std::vector<Task *> > &schedule, 
	int processors, int study_interval)
{
	for (int i = 0; i < processors; i++) {
		schedule.push_back(std::vector<Task *>());
		for (int j = 0; j < study_interval; j++) {
			schedule[i].push_back(NULL);	
		}
	}
}

void simulate_global(std::vector<Task> &tasks, int processors)
{
	// #processors enough for total utilisation?
	double utilization = total_utilization(tasks);
	
	int study_interval = interval(tasks);
	
	// vector of vectors to hold the scheduling of the system
	std::vector< std::vector<Task *> > schedule;
	
	// create n processor vectors which represent 1 processor each
	initialize_global_schedule(schedule, processors, study_interval);

	std::cout << "Total utilization of the system is " << utilization << std::endl;	
	// System can not be scheduled with the #processors
	if (utilization > (double)processors) {
		std::cout << "System is unable to be scheduled on this system with "
			<< processors << " processors. Determining the required number."
			<< std::endl;
		// setting processors to the minimum required number
		processors = ceil(utilization);
	// Otherwise, try the system specified by the user
	} else {
		if(do_simulate_global(tasks, processors, study_interval, schedule)) {
			display_scheduling(schedule, tasks);	
		} else {
			std::cout << "System not schedulable with " << processors 
				<< " processors. Determining the required number." 
				<< std::endl;
			//TODO hier weiter - loop bis do_simulate = true
		}
	}

}



bool do_simulate_global(std::vector<Task> &tasks, int processors, int study_interval, 
	std::vector< std::vector<Task *> > &schedule)
{
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
				for (unsigned scheduler_y = 0; scheduler_y < schedule.size(); scheduler_y++) {
					// find emtpy slot
					if ( NULL == schedule[scheduler_y][left]) {
						// Store pointer of current task in the slot
						schedule[scheduler_y][left] = &tasks[i];
						wcet_to_fill -= 1;
						/*
						----- This may be stupid to do? ---------- 
						*/
						// Left look ahead on the current processor for empty spots
						for (;wcet_to_fill > 0 && 			// There are still wcet to fill
							left + 1 < has_to_finish_at &&		// We are before the deadline
							NULL == schedule[scheduler_y][left+1];)	// There is a spot free on the right
						
						{
							schedule[scheduler_y][left+1] = &tasks[i];
							wcet_to_fill--;
							left++;
						}
						break;
					}
				}
				if (wcet_to_fill == 0) {
					break;
				}
			}
			// if there are still wcet left -> unable to schedule the system
			if (wcet_to_fill > 0) {	
				std::cout << "System is unable to be scheduled on this system. Try again with " 
					<< (processors + 1) << " processors." << std::endl;
				return false;
			}			

		}
	}
	return true;
	// displaying the schedule on the terminal
	//display_scheduling(schedule, tasks);
}


void simulate_partitioned(std::vector<Task> &tasks, int processors)
{

	std::cout << "I'm crying" << std::endl;

}





