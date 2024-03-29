#include <string>
#include <algorithm>
#include <iostream> //deleteme later
#include "usefull_methods.h"
#include "prioritySort.h"
#include "uniprocessorDM.h"


bool UniprocessorDM::simulate_system(std::vector<Task*> &tasks)
{	
	std::vector<Task *> schedule_tmp;
	return simulate_system(tasks, schedule_tmp);
}

bool UniprocessorDM::simulate_system(std::vector<Task*> &tasks, std::vector<Task*> &schedule)
{
	std::sort(tasks.begin(), tasks.end(), deadlinePriorityPointers);
	int study_interval = interval(tasks);
	// initialize schedule by creating empty spots
	for (int i = 0; i < study_interval; i++) {
		schedule.push_back(NULL);
	}

	// now simulate the tasks
	// ---------------------
	// Iterating every task
	for (unsigned i = 0; i < tasks.size(); i++) {
		this->_preemptions = 0;
		// Iterating every period of the task starting at the offset
		for (int position = tasks[i]->get_offset();
			position < study_interval;
			position += tasks[i]->get_period())
		{
			
			// Position by which the current task has to be finished
			int has_to_finish_at = position + tasks[i]->get_deadline();
		
			// nonono
			if (has_to_finish_at > study_interval) {
				break;
			}
			
			// How many slots we have to fill in the period
			int wcet_to_fill = tasks[i]->get_wcet();
			
			// Fill the processors from the left
			for (int left = position; 
				(left < has_to_finish_at) && (wcet_to_fill > 0); 
				left++)
			{
				
				if ( NULL == schedule[left]) {
					schedule[left] = tasks[i];
					wcet_to_fill -= 1;
				
					// fill up to the right to calculate preemptions
					while ((left+1 < has_to_finish_at) && (wcet_to_fill > 0)) {
						if (schedule[left+1] == NULL) {
							schedule[left+1] = tasks[i];
							wcet_to_fill -=1;
							left++;
						} 
						// otherwise the place is full -> preemption
						else {
							this->_preemptions++;
							break;
						}
					}

				}
			
			}
			// system was not schedulable
			if (wcet_to_fill > 0) {
				return false;
			}
		}
	}
	return true;	
}

bool UniprocessorDM::can_add_task(Task &task)
{
	// processor is empty, hence we can always add the task
	if (this->_tasks.empty()) {
		return true;
	}

	std::vector<Task*> tmp_tasks = this->_tasks;
	tmp_tasks.push_back(&task);

	// system of utilization larger than 1 is impossible of being scheduled
	if (total_utilization(tmp_tasks) > 1) {
		return false;
	}
	// TODO: check Utilization of ln2 
	return (simulate_system(tmp_tasks));	
}

void UniprocessorDM::add_task(Task &task)
{
	this->_tasks.push_back(&task);	
}


double UniprocessorDM::get_total_utilization()
{
	return total_utilization(this->_tasks);
}

int UniprocessorDM::get_study_interval()
{
	return interval(this->_tasks);
}

int UniprocessorDM::get_preemptions()
{
	return this->_preemptions;
}

std::vector<Task *> UniprocessorDM::get_schedule()
{
	std::vector<Task *> schedule;
	simulate_system(this->_tasks ,schedule);	
	return schedule;
}

