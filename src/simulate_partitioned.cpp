#include <iostream>
#include "task.h"
#include <vector>
#include "uniprocessorDM.h"
#include "simulate_partitioned.h"

void simulate_partitioned(std::vector<Task> &tasks, int processors)
{
	std::cout << "hello" << std::endl;
	UniprocessorDM p1;
	//std::cout << p1.can_add_task(tasks[0]) << std::endl;
	
	p1.add_task(tasks[0]);
	p1.add_task(tasks[1]);
	
	p1.add_task(tasks[2]);
	
	std::cout << p1.get_total_utilization() << std::endl;
}
