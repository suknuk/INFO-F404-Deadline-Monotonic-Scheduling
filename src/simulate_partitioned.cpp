#include <iostream>
#include <algorithm>
#include "prioritySort.h"
#include "uniprocessorDM.h"
#include "usefull_methods.h"
#include "simulate_partitioned.h"

//std::vector< std::vector<Task*> > 
//std::vector <std::vector<Task*> >
void simulate_partitioned(std::vector<Task> &tasks, int processors)
{
	// Sort tasks by utilization for 'bin fitting'
	std::sort(tasks.begin(), tasks.end(), utilizationPriority);
	for (unsigned i = 0; i < tasks.size(); i++)
	{
		std::cout << tasks[i].get_uid() << std::endl;
	}
	
	std::vector<Task*> single_schedule;

	UniprocessorDM proc[1];
	
	proc[0].add_task(tasks[0]);
	single_schedule = proc[0].get_schedule();		
	std::vector< std::vector<Task*> > schedule;
	schedule.push_back(single_schedule);
	display_scheduling(schedule);
//	return schedule;
}


