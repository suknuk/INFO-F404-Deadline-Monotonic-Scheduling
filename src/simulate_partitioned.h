#ifndef SIMULATE_PARTITIONED_H
#define SIMULATE_PARTITIONED_H

#include <vector>
#include "uniprocessorDM.h"
#include "task.h"

std::vector <std::vector<Task*> > simulate_partitioned(std::vector<Task> &tasks, int processors, 
		std::vector<int> &preemptions);

bool do_simulate_partitioned(std::vector<Task> &tasks, int processors, std::vector<UniprocessorDM> &schedule);

// Calculating the min. required processors
int minimum_partitioned_processors_required(std::vector<Task> &tasks, std::vector<UniprocessorDM> &schedule);

// transform the vector of UniprocessorDM to a vector of vector of Task*
std::vector <std::vector<Task*> > uniprocessors_to_vector(std::vector<UniprocessorDM> &uniprocessors,
		std::vector<int> &preemptions);

#endif
