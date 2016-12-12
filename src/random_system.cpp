#include <iostream>
#include <cstdlib>
#include <ctime>
#include "usefull_methods.h"
#include "random_system.h"

// TODO calculate the lcm so that it does not get too high!

void RandomSystem::generate_system()
{
	std::srand(std::time(0));
	// create a random max_Period between 9 + #tasks*2  and 100 
	int max_period = std::rand() % (91 - this->_tasks*2 )  + ( 9 + this->_tasks*2) ;
	std::cout << "Max period = " << max_period << std::endl;

	std::vector<double> utilization;
	double total_generated_utilization = 0;
	
	// generate n-tasks random utilization factors
	for (int i = 0; i < this->_tasks; i++) {
		double rnd_utilization = std::rand() % 99 + 1;// between 1 and 100
		utilization.push_back( rnd_utilization ); 
		total_generated_utilization += rnd_utilization;
	}

	// now make the generated total utilization equal to the target utilization
	for (int i = 0; i < this->_tasks; i++) {
		utilization[i] = (utilization[i] / total_generated_utilization) * this->_utilization;
	}

	// carry value that takes over the utilization factor that was over or under achieved by 
	// the previous tasks
	double utilization_carry = 0;

	// store the LCM, otherwise, with too many tasks, we might get a value too large
	int total_lcm = 1;

	//std::vector<Task> tasks;
	// find values that try to match the utilization given by the generated utilization value
	for (int i = 0; i < this->_tasks; i++) {
		
		int offset = std::rand() % (max_period/2);

		int best_wcet = 1;
		int best_period = 1;
		double best_carry = 0;
		double lowest_diff = 101; // 101% is the worst value possible

		// iterate every deadline
		for (int period = 1; period <= max_period; period++) {
			// iterate every period
			for (int wcet = 1; wcet <= period; wcet++) {
				// what is the utilization of these values?
				double tmp_u = (double(wcet)/double(period)) * 100;
			
				// add the Utilization carry so we can get closer the the wanted result
				double diff = utilization[i] + utilization_carry - tmp_u;
				// cast positive if negative
				if (diff < 0) {
					diff = diff * -1; 
				}

				// new best match?
				if (diff < lowest_diff) {
					best_wcet = wcet;
					best_period = period;
					lowest_diff = diff;
					best_carry = utilization[i] + utilization_carry - tmp_u ;
				} 
			}
		}

		// the new total lcm
		int tmp_lcm = lcm(total_lcm, best_period);

		// new lcm too large?
		if (tmp_lcm > this->_max_hyper_period) {
			// take random period already existing in the tasks
			int new_period = _tasks_vector[std::rand() % _tasks_vector.size()].get_period();
			
			//store the difference of the old vs new 
			double difference = double(new_period)/double(best_period);

			//now change the other task variables according to this %
			best_period = new_period;
			best_wcet =  best_wcet * difference;
			
			// special case of 0 wcet
			if (best_wcet < 1) {
				best_wcet = 1;
			}
		}

		total_lcm = tmp_lcm;

		// take over the best carry value
		utilization_carry = best_carry;

		// get a deadline between wcet and the period
		int deadline;
		
		// case when Utilization is at 100%
		if (best_period == best_wcet) {
			deadline = best_period;
		} else {
			deadline = std::rand() % (best_period - best_wcet) + best_wcet;
		}

		// add new task with the values to the vector
		Task task(offset, best_period, deadline, best_wcet);
		this->_tasks_vector.push_back(task);
	}

	// When the carry value is too big, go back to the list and look where we can increase
	// the Utilization of single tasks to make it closer to the wanted value
	if (total_utilization(_tasks_vector)*100 - this->_utilization > 2 || 
		total_utilization(_tasks_vector)*100 - this->_utilization < -2) {	
		
		for (unsigned i = 0; i < _tasks_vector.size(); i++) {
			// increase the utilization until 100% or the target total utilization is reached
			while( _tasks_vector[i].calculate_utilization() < 1 &&
				(total_utilization(_tasks_vector)*100 - this->_utilization > 2 ||
				total_utilization(_tasks_vector)*100 - this->_utilization < -2) ) {

				// increase the deadline if needed
				if (_tasks_vector[i].get_deadline() < _tasks_vector[i].get_period() && 
					_tasks_vector[i].get_deadline() == _tasks_vector[i].get_wcet()) {
					_tasks_vector[i].set_deadline( _tasks_vector[i].get_deadline() + 1);
				}

				double utilization_before = total_utilization(_tasks_vector)*100 - this->_utilization;

				// increase wcet by 1 if U > 0, otherwise subtract by 1
				int add_or_sub;
				if (total_utilization(_tasks_vector)*100 - this->_utilization > 0) {
					add_or_sub = -1;
				} else {
					add_or_sub = 1;
				}

				_tasks_vector[i].set_wcet(_tasks_vector[i].get_wcet() + add_or_sub);
				
				double utilization_after = total_utilization(_tasks_vector)*100 - this->_utilization;
				
				// cast positive for easier comparison
				if (utilization_before < 0) {
					utilization_before *= -1;
				}
				if (utilization_after < 0) {
					utilization_after *= -1;
				}

				// did this increase help to reach the target U or did it make it worse?
				if (utilization_before < utilization_after) {
					// made it worse! 
					// undo the step
					_tasks_vector[i].set_wcet(_tasks_vector[i].get_wcet() - 1);
					// go to next task
					break; // quits the while loop
				}
			}
		}
	} // finished filling up wcet if needed	
	
}

RandomSystem::RandomSystem(int tasks, int utilization, int max_hyper_period)
{
	this->_tasks = tasks;
	this->_utilization = utilization;
	this->_max_hyper_period = max_hyper_period;
	generate_system();
}

std::vector<Task> RandomSystem::get_tasks()
{
	return this->_tasks_vector;
}
