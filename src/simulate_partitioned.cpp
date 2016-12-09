#include <iostream>
#include <vector>
#include <algorithm>
#include "task.h"
#include "prioritySort.h"
#include "uniprocessorDM.h"
#include "simulate_partitioned.h"

void simulate_partitioned(std::vector<Task> &tasks, int processors)
{
	// Sort tasks by utilization for 'bin fitting'
	std::sort(tasks.begin(), tasks.end(), utilizationPriority);
	
	UniprocessorDM schedule[processors];
	
	schedule[0].can_add_task(tasks[0]);	
	schedule[0].can_add_task(tasks[0]);

	schedule[0].add_task(tasks[0]);
	schedule[0].add_task(tasks[1]);
	
	schedule[0].add_task(tasks[2]);
	
	std::cout << schedule[0].get_total_utilization() << std::endl;
}
