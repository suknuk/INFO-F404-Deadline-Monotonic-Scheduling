#include "task.h"

Task::Task (int offset, int period, int deadline, int wcet)
{
	this->offset = offset;
	this->period = period;
	this->deadline = deadline;
	this->wcet = wcet;
}

double Task::calculate_utilization() const
{	
	return static_cast<double>(this->wcet) / static_cast<double>(this->period);
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

bool operator<(const Task &t1, const Task &t2)
{
	return t1.get_deadline() < t2.get_deadline();
}



