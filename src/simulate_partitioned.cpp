#include <iostream>
#include "task.h"
#include <vector>
#include "uniprocessorDM.h"
#include "simulate_partitioned.h"

void simulate_partitioned(std::vector<Task> &tasks, int processors)
{
	UniprocessorDM schedule[processors];
	
	schedule[0].can_add_task(tasks[0]);	
	schedule[0].can_add_task(tasks[0]);

	schedule[0].add_task(tasks[0]);
	schedule[0].add_task(tasks[1]);
	
	schedule[0].add_task(tasks[2]);
	
	std::cout << schedule[0].get_total_utilization() << std::endl;
}
