#include <string>
#include "usefull_methods.h"
#include "uniprocessorDM.h"


bool UniprocessorDM::simulate_system(std::vector<Task> &tasks)
{
	int study_interval = interval(tasks);
	std::vector<Task *> schedule;
	for (int i = 0; i < study_interval; i++) {
		schedule.push_back(NULL);
	}

	return true;	
}
bool UniprocessorDM::can_add_task(Task &task)
{
	if (this->_tasks.empty()) {
		return true;
	}
	std::vector<Task> tmp_tasks = this->_tasks;
	tmp_tasks.push_back(task);
	return (simulate_system(tmp_tasks));	
}

void UniprocessorDM::add_task(Task &task)
{
	this->_tasks.push_back(task);	
}

double UniprocessorDM::get_total_utilization()
{
	return total_utilization(this->_tasks);
}

int UniprocessorDM::get_study_interval()
{
	return 0;
}

std::vector<Task *> UniprocessorDM::get_schedule()
{
	std::vector<Task *> schedule;
	return schedule;
}
