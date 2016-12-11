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

	std::vector<UniprocessorDM> schedule;
	
	// system can't be scheduled with the given parameters
	if (utilization > double(processors) || !(do_simulate_partitioned(tasks, processors, schedule))) {
		std::cout << "System is unable to be scheduled on this system with "
			<< processors << " processors. Determining the required number."
			<< std::endl;
		// setting processors to the minimum required number -> has to be at least the #utilization
		if (processors < ceil(utilization)) {
			processors = ceil(utilization);
		}
		// find min. required processors
		processors = minimum_partitioned_processors_required(tasks, schedule);
		std::cout << "Number of processors required : " << processors << std::endl;
	} else {
		// System can be scheduled, are less processors possible?
		std::vector<UniprocessorDM> tmp_schedule;
		int min_processors = minimum_partitioned_processors_required(tasks, tmp_schedule);
		if (min_processors < processors) {
			std::cout << "System could have been scheduled with " << min_processors << " processors."
				<< std::endl;
		} else {
		 	std::cout << processors << " is the least required # of processors to schedule this system."
				<< std::endl;
		}
	}
	return uniprocessors_to_vector(schedule); 
}

bool do_simulate_partitioned(std::vector<Task> &tasks, int processors, std::vector<UniprocessorDM> &schedule)
{
	schedule.clear();
	for (int i = 0; i < processors; i++) {
		schedule.push_back(UniprocessorDM());
	}

	// Iterate every task
	for (unsigned task_nr = 0; task_nr < tasks.size(); task_nr++) {
		// default values
		int best_processor_assignment = -1; 	// -1 -> no assignment
		double best_utilization = 0; 		//best utilization is 1, worst is 0 -> we want 1
		
		//Iterate every uniprocessor 
		for (unsigned process_nr = 0; process_nr < schedule.size(); process_nr++) {
			// can task be scheduled on current uniprocessor?
			if (schedule[process_nr].can_add_task(tasks[task_nr])) {
				double utilization = schedule[process_nr].get_total_utilization() + tasks[task_nr].calculate_utilization();
				// new best best fit?
				if (utilization > best_utilization) {
					best_utilization = utilization;
					best_processor_assignment = (int) process_nr;
				}
			}
		}
		// we now checked every uniprocessor
		// take best assignment, if it exists, and add the task to the uniprocessor
		if (best_processor_assignment == -1) {
			return false;
		} else { 
			schedule[best_processor_assignment].add_task(tasks[task_nr]);
		}
	}
	return true;
}

int minimum_partitioned_processors_required(std::vector<Task> &tasks, std::vector<UniprocessorDM> &schedule)
{
	// min #processors has to be at least the total utilization rounded up
	int processors = ceil(total_utilization(tasks));

	// now we simulate the system until we find the required processors
	while (!do_simulate_partitioned(tasks, processors, schedule)) {
		processors++;
	}

	return processors;
}

std::vector <std::vector<Task*> > uniprocessors_to_vector(std::vector<UniprocessorDM> &uniprocessors)
{
	std::vector< std::vector<Task*> > schedule_final;

	for (unsigned processor = 0; processor < uniprocessors.size(); processor++) {
		schedule_final.push_back(uniprocessors[processor].get_schedule());
	}	

	return schedule_final;
}
