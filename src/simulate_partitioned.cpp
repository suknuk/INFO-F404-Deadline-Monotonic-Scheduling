#include <iostream>
#include <algorithm>
#include <cmath>
#include "prioritySort.h"
#include "uniprocessorDM.h"
#include "usefull_methods.h"
#include "simulate_partitioned.h"

std::vector <std::vector<Task*> > simulate_partitioned(std::vector<Task> &tasks, int processors)
{
	// Sort tasks by utilization for 'bin fitting'
	std::sort(tasks.begin(), tasks.end(), utilizationPriority);
	
	double utilization = total_utilization(tasks);
	
	std::vector< std::vector<Task*> > schedule_final;
	std::vector<UniprocessorDM> schedule;

	// system can't be scheduled with the given parameters
	if (utilization > double(processors) || do_simulate_partitioned(tasks, processors, schedule)) {
		std::cout << "System is unable to be scheduled on this system with "
			<< processors << " processors. Determining the required number."
			<< std::endl;
		// setting processors to the minimum required number -> has to be at least the #utilization
		if (processors < ceil(utilization)) {
			processors = ceil(utilization);
		}
		// find min. required processors
		// TODO -->
		//processors = minimul_global_processors_required(tasks, schedule, processors, study_interval);
		std::cout << "Number of processors required : " << processors << std::endl;
	} else {
		// System can be scheduled
	}


	/*
	for (unsigned i = 0; i < tasks.size(); i++)
	{
		std::cout << "i: " << i << " ID: " << tasks[i].get_uid() << " U: " << tasks[i].calculate_utilization() << std::endl;
	}
	
	std::vector<Task*> single_schedule;
	UniprocessorDM proc;
	std::cout << "can add task 3 : " << proc.can_add_task(tasks[3]) << std::endl;
	proc.add_task(tasks[3]);
	std::cout << "can add task 2 : " << proc.can_add_task(tasks[2]) << std::endl;
	proc.add_task(tasks[2]);
	std::cout << "can add task 1 : " << proc.can_add_task(tasks[1]) << std::endl;
	single_schedule = proc.get_schedule();		
	schedule.push_back(single_schedule);*/
	return schedule_final;
}

bool do_simulate_partitioned(std::vector<Task> &tasks, int processors, std::vector<UniprocessorDM> &schedule)
{
	// Iterate every task
	for (unsigned task_nr = 0; task_nr < tasks.size(); task_nr++) {
		int best_processor_assignment = -1;
		double best_utilization = 1;
		
		//Iterate every uniprocessor 
		for (unsigned process_nr = 0; process_nr < schedule.size(); process_nr++) {
			// can it be scheduled?
			if (schedule[process_nr].can_add_task(tasks[task_nr])) {
				double utilization = schedule[process_nr].get_total_utilization() + tasks[task_nr].calculate_utilization();
				// new best best fit?
				if (utilization < best_utilization) {
					best_utilization = utilization;
					best_processor_assignment = (int) process_nr;
				}
			}
		}
		// we now checked every uniprocessor
		// take best assignment, if it exists, and add the task to the uniprocessor
		// TODO continue here!
	}
	return false;
}




