#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "usefull_methods.h"
#include "prioritySort.h"
#include "simulate_global.h"

void initialize_global_schedule(std::vector< std::vector<Task *> > &schedule, 
	int processors, int study_interval)
{
	std::cout << "init 1, size: " << schedule.size() << std::endl;
	schedule.clear();
	std::cout << "init 2" << std::endl;
	for (int i = 0; i < processors; i++) {
		schedule.push_back(std::vector<Task *>());
		for (int j = 0; j < study_interval; j++) {
			schedule[i].push_back(NULL);	
		}
	}
}

int minimum_global_processors_required(std::vector<Task> &tasks, std::vector< std::vector<Task*> > &schedule, 
	int processors, int study_interval)
{
	std::cout << "before init " << std::endl;
	// we have to reset the schedule vector as it has data in it and processors could be changed
	initialize_global_schedule(schedule, processors, study_interval);
	std::cout << "after init " << std::endl;

	// Iterate until system is schedulable with the given processors
	while(false == do_simulate_global(tasks, study_interval, schedule))
	{
		//std::cout << processors << std::endl;
		processors += 1;

		std::cout << "before init loop " << std::endl;
		initialize_global_schedule(schedule, processors, study_interval);
		std::cout << "after init loop " << std::endl;
	}
	std::cout << "before return " << processors << std::endl;
	return processors;
}

std::vector <std::vector<Task*> > simulate_global(std::vector<Task> &tasks, int processors)
{
	//Sorting the tasks according to their deadline
	std::sort(tasks.begin(), tasks.end(), deadlinePriority);
	
	double utilization = total_utilization(tasks);
	
	int study_interval = interval(tasks);
	
	// vector of vectors to hold the scheduling of the system
	std::vector< std::vector<Task *> > schedule;
	
	// create n processor vectors which represent 1 processor each
	initialize_global_schedule(schedule, processors, study_interval);

	std::cout << "Total utilization of the system is " << utilization << std::endl
		<< "Study interval of the system is " << study_interval << std::endl;	
	// System can not be scheduled with the #processors
	if (utilization > (double)processors || !do_simulate_global(tasks,  study_interval, schedule)) {
		std::cout << "System is unable to be scheduled on this system with "
			<< processors << " processors. Determining the required number."
			<< std::endl;
		// setting processors to the minimum required number -> has to be at least the #utilization
		if (processors < ceil(utilization)) {
			processors = ceil(utilization);
		}
		// find min. required processors
		processors = minimum_global_processors_required(tasks, schedule, processors, study_interval);
		std::cout << "Number of processors required : " << processors << std::endl;
	} else {
		// System can be scheduled
		// possible that we can schedule it with fewer tasks?
		if (processors > ceil(utilization)) {
			// use a tmp schedule because we want to return the original schedule, not the optimized one
			std::vector <std::vector<Task*> > schedule_tmp;
			// we look between ceil(utilization) and processors
			int min_processors = minimum_global_processors_required(tasks, schedule_tmp, ceil(utilization), study_interval);
			if (min_processors < processors){
				std::cout << "System could have been scheduled with " << min_processors << " processors."
					<< std::endl;
			} else {
				std::cout << processors << " is the least required # of processors to schedule this system."
					<< std::endl;
			}

		} else {
			std::cout << processors << " is the least required # of processors to schedule this system."
				<< std::endl;
		}	
	}
	return schedule;
}

bool do_simulate_global(std::vector<Task> &tasks, int study_interval, 
	std::vector< std::vector<Task *> > &schedule)
{
//	std::cout << "do 1" << std::endl;
	// Iterating every task by priority 
	for (unsigned i = 0; i < tasks.size(); i++) {
		// Iterating every period of the task starting at the offset
		for (int position = tasks[i].get_offset(); 
			position < study_interval;
			position += tasks[i].get_period())
		{
	//		std::cout << "do 2"<< std::endl;
			// Position by which the current task has to be finished
			int has_to_finish_at = position + tasks[i].get_deadline();
			// How many slots we have to fill in the period
			int wcet_to_fill = tasks[i].get_wcet();
			
	//		std::cout << "do 3"<< std::endl;
			// Fill the processors from the left
			for (int left = position; left < has_to_finish_at; left++){
				for (unsigned scheduler_y = 0; scheduler_y < schedule.size(); scheduler_y++) {
					// find emtpy slot
					if ( NULL == schedule[scheduler_y][left]) {
						// Store pointer of current task in the slot
		//				std::cout << "do 4"<< std::endl;
						schedule[scheduler_y][left] = &tasks[i];
		//				std::cout << "do 5"<< std::endl;
						wcet_to_fill -= 1;
						
						// Left look ahead on the current processor for empty spots
						for (;wcet_to_fill > 0 && 			// There are still wcet to fill
							left + 1 < has_to_finish_at &&		// We are before the deadline
							NULL == schedule[scheduler_y][left+1];)	// There is a spot free on the right
						
						{
		//	std::cout << "do 6"<< std::endl;
							schedule[scheduler_y][left+1] = &tasks[i];
		//	std::cout << "do 7"<< std::endl;
							wcet_to_fill--;
							left++;
						}
						break;
					}
				}
				// no more slots to fill -> next period
				if (wcet_to_fill == 0) {
					break;
				}
			}
			// if there are still wcet left -> unable to schedule the system
			if (wcet_to_fill > 0) {	
				return false;
			}			
		}
	}
	std::cout << "do end"<< std::endl;
	// System is schedulable
	return true;
}
