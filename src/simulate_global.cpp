#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "usefull_methods.h"
#include "prioritySort.h"
#include "pretty_output.h"
#include "simulate_global.h"

void initialize_global_schedule(std::vector< std::vector<Task *> > &schedule, 
	int processors, int study_interval)
{
	schedule.clear();
	for (int i = 0; i < processors; i++) {
		schedule.push_back(std::vector<Task *>());
		for (int j = 0; j < study_interval; j++) {
			schedule[i].push_back(NULL);	
		}
	}
}

int minimul_global_processors_required(std::vector<Task> &tasks, std::vector< std::vector<Task*> > &schedule, 
	int processors, int study_interval)
{
	// we have to reset the schedule vector as it has data in it and processors could be changed
	initialize_global_schedule(schedule, processors, study_interval);
	
	// Iterate until system is schedulable with the given processors
	while(false == do_simulate_global(tasks, processors, study_interval, schedule))
	{
		std::cout << processors << std::endl;
		processors += 1;
		initialize_global_schedule(schedule, processors, study_interval);
	}
	return processors;
}

std::vector <std::vector<Task*> > simulate_global(std::vector<Task> &tasks, int processors)
{
	//Sorting the tasks according to their deadline
	std::sort(tasks.begin(), tasks.end(), deadlinePriority);
	
	// #processors enough for total utilisation?
	double utilization = total_utilization(tasks);
	
	int study_interval = interval(tasks);
	
	// vector of vectors to hold the scheduling of the system
	std::vector< std::vector<Task *> > schedule;
	
	// create n processor vectors which represent 1 processor each
	initialize_global_schedule(schedule, processors, study_interval);

	std::cout << "Total utilization of the system is " << utilization << std::endl
		<< "Study interval of the system is " << study_interval << std::endl;	
	// System can not be scheduled with the #processors
	if (utilization > (double)processors || !do_simulate_global(tasks, processors, study_interval, schedule)) {
		std::cout << "System is unable to be scheduled on this system with "
			<< processors << " processors. Determining the required number."
			<< std::endl;
		// setting processors to the minimum required number -> has to be at least the #utilization
		if (processors < ceil(utilization)) {
			processors = ceil(utilization);
		}
		// find min. required processors
		processors = minimul_global_processors_required(tasks, schedule, processors, study_interval);
		std::cout << "Number of processors required : " << processors << std::endl;
	} else {
		// System can be scheduled
		// possible that we can schedule it with fewer tasks?
		if (processors > ceil(utilization)) {
			// use a tmp schedule because we want to return the original schedule, not the optimized one
			std::vector <std::vector<Task*> > schedule_tmp;
			// we look between ceil(utilization) and processors
			int min_processors = minimul_global_processors_required(tasks, schedule_tmp, ceil(utilization), study_interval);
			if (min_processors < processors){
				std::cout << "System could have been scheduled with " << min_processors << " processors."
					<< std::endl;
			}
		}	
	}
	return schedule;
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
	// System is schedulable
	return true;
}
