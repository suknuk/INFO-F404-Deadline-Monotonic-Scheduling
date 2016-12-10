#ifndef SIMULATE_PARTITIONED_H
#define SIMULATE_PARTITIONED_H

#include <vector>
#include "uniprocessorDM.h"
#include "task.h"

std::vector <std::vector<Task*> > simulate_partitioned(std::vector<Task> &tasks, int processors);

bool do_simulate_partitioned(std::vector<Task> &tasks, int processors, std::vector<UniprocessorDM> &schedule);

// transform the vector of UniprocessorDM to a vector of vector of Task*
std::vector <std::vector<Task*> > uniprocessors_to_vector(std::vector<UniprocessorDM> &uniprocessors);

#endif
