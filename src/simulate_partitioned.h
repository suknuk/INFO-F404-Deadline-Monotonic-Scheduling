#ifndef SIMULATE_PARTITIONED_H
#define SIMULATE_PARTITIONED_H

#include <vector>
#include "task.h"

std::vector <std::vector<Task*> > simulate_partitioned(std::vector<Task> &tasks, int processors);

bool do_simulate_partitioned(std::vector<Task> &tasks, int processors, std::vector<UniprocessorDM> &schedule);

#endif
