#include "task.h"

Task::Task (int offset, int period, int deadline, int wcet)
{
	this->offset = offset;
	this->period = period;
	this->deadline = deadline;
	this->wcet = wcet;
}

int Task::calculate_utilization()
{
	return 0;
}

int Task::get_offset() const
{
	return this->offset;
}

int Task::get_period() const
{	
	return this->period;
}

int Task::get_deadline() const
{
	return this->deadline;
}

int Task::get_wcet() const
{
	return this->wcet;
}
