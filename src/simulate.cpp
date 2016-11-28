#include <string>
#include "usefull_methods.h"
#include "simulate.h"

void simulate_global(std::vector<Task> &tasks, int processors)
{
	// #processors enough for total utilisation?
	double utilization = total_utilization(tasks); 	
}
