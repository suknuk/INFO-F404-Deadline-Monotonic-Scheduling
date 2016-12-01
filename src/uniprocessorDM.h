#ifndef UNIPROCESSORDM_H
#define UNIPROCESSORDM_H

#include <vector>
#include "task.h"

class UniprocessorDM
{
private:
	std::vector<Task> _tasks;

	bool simulate_system(std::vector<Task> &tasks);
public:
	// checking if a task can be added
	bool can_add_task(Task &task);
	void add_task(Task &task);

	// getters
	double get_total_utilization();
	int get_study_interval();

	// calculate the DM schedule with the tasks in tasks
	std::vector<Task *> get_schedule();
};

#endif
