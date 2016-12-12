#ifndef RANDOM_SYSTEM_H 
#define RANDOM_SYSTEM_H

#include <vector>
#include "task.h"

class RandomSystem
{
	private:
		int _tasks, _utilization, _max_hyper_period;
		std::vector<Task> _tasks_vector;
		void generate_system();
	public:
		RandomSystem(int,int,int);
		std::vector<Task> get_tasks();

};

#endif
