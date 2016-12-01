#ifndef UNIPROCESSORDM_H
#define UNIPROCESSORDM_H

#include <vector>
#include "task.h"

class UniprocessorDM
{
private:
	std::vector<Task> tasks;
	std::vector<Task *> schedule;
public:
	// checking if a task can be added
	bool can_add_task(Task &task);
	void add_task(Task &task);

	// getters
	int get_total_utilization();
	int get_study_interval();

	std::vector<Task *> get_schedule();
};

#endif
