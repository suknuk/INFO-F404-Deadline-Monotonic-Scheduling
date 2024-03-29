#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "usefull_methods.h"
#include "task.h"
#include "simulate_global.h"
#include "simulate_partitioned.h"
#include "prioritySort.h"

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
		bool show_scheduling = false;
		// display the scheduled tasks in the console flag?
		if (argc == 5) {
			std::string args(argv[4]);
			if (args != "-d") {
				std::cerr << "To display the scheduling in the console, the flag -d must be used"
					<< std::endl;
				show_usage(argv[0]);
				return 1;
			}
			show_scheduling = true;
		}

		// Stating the mode with input data that will be executed
		std::cout << "Simulating system described in " << file_name << " in the "
			<< ((scheduling_type)?"global":"partitioned") << " strategy with "
			<< processors << " processors." << std::endl;

		// getting vector of tasks
		std::vector<Task> tasks = read_tasks_file(argv[2]);

		// show tasks information to the user
		display_tasks(tasks);	

		std::vector <std::vector<Task *> > schedule;
		std::vector <int> preemptions;

		if (scheduling_type) {
			schedule = simulate_global(tasks, processors, preemptions);
		} else {
			schedule = simulate_partitioned(tasks, processors, preemptions);
		}

		display_scheduling(schedule, show_scheduling, preemptions);	
		
		return 0;
	}
		
	show_usage(argv[0]);
	return 1;
}
