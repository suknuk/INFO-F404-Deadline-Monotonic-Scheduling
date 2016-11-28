#include <iostream>
#include <string>
#include "usefull_methods.h"
#include "task.h"
#include <vector>
#include <algorithm>
#include "simulate.h"

int main(int argc, char* argv[])
{
	// false -> partitioned, true -> global
	bool scheduling_type;
	std::string file_name;
	int processors;

	// Checking argument input size
	if (argc < 4 || argc > 5) {
		std::cerr << "Wrong number of arguments!" << std::endl;
	}
	// Checking -p | -g
	else if (!is_arg_p_or_g(argv[1], scheduling_type)) {
		std::cerr << "Unrecognized argument " << argv[1] << std::endl;
	} 
	// Checking tasks file
	else if (!does_file_exist(argv[2], &file_name)){
		std::cerr << argv[2] << " cannot be opened" << std::endl;
	}
	// Checking if <processorsNbr> is a integer
	else if (!is_number(argv[3], &processors))
	{
		std::cerr << "Number of processors must be a integer" << std::endl;		
	}
	else 
	{
		// Stating the mode with input data that will be executed
		std::cout << "Simulating system described in " << file_name << " in the "
			<< ((scheduling_type)?"global":"partitioned") << " strategy with "
			<< processors << " processors." << std::endl;

		// getting vector of tasks
		std::vector<Task> tasks = read_tasks_file(argv[2]);
		std::sort(tasks.begin(), tasks.end());

		std::cout << "Offset\t\tPeriod\t\tDeadline\tWCET\t\tUtilization" << std::endl;

		for (unsigned i = 0; i < tasks.size(); i++) {
			std::cout << tasks[i].get_offset() << "\t\t" 
				<< tasks[i].get_period() << "\t\t" 
				<< tasks[i].get_deadline() << "\t\t" 
				<< tasks[i].get_wcet() << "\t\t"
				<< tasks[i].calculate_utilization()
				<< std::endl;
		}

		if (scheduling_type) {
			simulate_global(tasks, processors);
		} else {
			// Simulate partitioned
		}
		
		return 0;
	}
		
	show_usage(argv[0]);
	return 1;
}
