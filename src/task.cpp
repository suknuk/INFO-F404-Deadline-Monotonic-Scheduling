#include "task.h"
#include <stdexcept>
#include <iostream>

int UID_counter = 1; 

Task::Task (int offset, int period, int deadline, int wcet)
{
	// We only consider constrained deadlines, so we do a check
	if (deadline > period) {
		throw std::invalid_argument("Only constrained deadlines are allowed.");
	}
	this->offset = offset;
	this->period = period;
	this->deadline = deadline;
	this->wcet = wcet;
	this->uid = UID_counter++;
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

int Task::get_uid() const
{
	return this->uid;
}

void Task::set_deadline(int deadline)
{
	this->deadline = deadline;
}

void Task::set_wcet(int wcet)
{
	this->wcet = wcet;
}

bool operator<(const Task &t1, const Task &t2)
{
	// sort by deadline first as it is DM
	if (t1.get_deadline() < t2.get_deadline()){
		return true;
	} else if (t1.get_deadline() > t2.get_deadline()) {
		return false;
	// ow deadlines are equal
	} else {
		// utilization secondly
		if (t1.calculate_utilization() > t2.calculate_utilization()) { 	
			return  true; 
			
		} else if (t1.calculate_utilization() > t2.calculate_utilization()) {
			return false;
		// utilization also equal
		} else {
			//offset thirdly
			if (t1.get_offset() < t2.get_offset()) {
				return true;
			} else if (t1.get_offset() > t2.get_offset()) {
				return false;
			// ow they are equal in deadline, utilization and offset
			} else {
				return true;
			}
		}
	}
	//old-- return t1.get_deadline() < t2.get_deadline();
}



