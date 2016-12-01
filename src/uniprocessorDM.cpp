#include "uniprocessorDM.h"


bool UniprocessorDM::can_add_task(Task &task)
{
	if (this->tasks.empty()) {
		return true;
	}
	return true;	
}

void UniprocessorDM::add_task(Task &task)
{
	
}

int UniprocessorDM::get_total_utilization()
{
	return 0;
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
