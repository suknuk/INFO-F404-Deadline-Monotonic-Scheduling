#ifndef SIMULATE_H
#define SIMULATE_H

#include <vector>
#include "task.h"

// Initializing the global schedule by creating the processors with length processors
void initialize_global_schedule(std::vector< std::vector<Task*> > &schedule, 
	int processors, int study_interval);

// Calculating the minimul # of required processors
int minimul_processors_required(std::vector<Task> &tasks, std::vector< std::vector<Task*> > &schedule,
	int processors, int study_interval);

// Calling the simulation for the processors required
void simulate_global(std::vector<Task> &tasks, int processors);

// Simulating using the global strategy
bool do_simulate_global(std::vector<Task> &tasks, int processors, int study_interval,
	std::vector< std::vector<Task*> > &schedule);

// Simulating using the partitioned strategy
void simulate_partitioned(std::vector<Task> &tasks, int processors);

#endif
