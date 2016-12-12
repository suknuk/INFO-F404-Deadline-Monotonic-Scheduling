#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "task.h"
#include "usefull_methods.h"
#include "random_system.h"

void show_task_generation_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " -u <UtilizationFactor> -n <tasksNumber>"
		<< " -o <OutputFile> [ -hp <hyperPeriod> ]\n"
		<< "\t-u <UtilizationFactor>\tInteger utilization of the system\n"
		<< "\t-n <tasksNumber>\tInteger number of tasks of the system\n"
		<< "\t-o <OutputFile>\t\tPath to the to be written file\n"
		<< "\t [ -hp <hyperPeriod>\tSoft limit for the  hyper period of generated tasks (int) -  20000 default. ]"
		<< std::endl;
}

void write_tasks_to_file(std::vector<Task> &tasks, std::string &file_name)
{
	std::ofstream out(file_name.c_str());
	
	for (unsigned i = 0; i < tasks.size(); i++){
		out << tasks[i].get_offset() << " " 
			<< tasks[i].get_period() << " "
			<< tasks[i].get_deadline() << " "
			<< tasks[i].get_wcet()
			<< '\n';
	}

	out.close();
}

int main(int argc, char* argv[])
{

	// default hyper period
	int hyper_period = 20000;

	// # of arguments
	if (argc < 7 || argc > 9 || argc == 8) {
		std::cerr << "Wrong number of arguments!" << std::endl;
		show_task_generation_usage(argv[0]);
		return 1;
	} 

	// transforming to string to make comparison easier
	std::string args [argc];
	for (int i = 0; i < argc; i++) {
		args[i] = argv[i];
	}

	int utilization_factor;
	int tasks;
	std::string output_file;

	// Check "-u" usage %
	if (args[1] != "-u") {
		std::cerr << args[1] << " must be -u" << std::endl;
	}
	// get Utilization factor
	else if(!is_number(argv[2], &utilization_factor)) {
		std::cerr << "Utilization factor must be an integer" << std::endl;		
	}
	// Check "-n" tasks
	else if (args[3] != "-n") {
		std::cerr << args[3] << " must be -n" << std::endl;
	}
	// get # of tasks
	else if(!is_number(argv[4], &tasks)) {
		std::cerr << "# Tasks must be an integer" << std::endl;		
	}
	// Check "-o" output
	else if (args[5] != "-o") {
		std::cerr << args[5] << " must be -o" << std::endl;
	}
	
	// hyper period flag and int given?
	else if (argc == 9 && args[7] != "-hp") {
		std::cerr << args[7] << " must be -hp" << std::endl;
	}

	else {
		// check hyper period int
		if (argc == 9) {
			// get hyper period when given an integer
			if (!is_number(argv[8], & hyper_period)) {
				std::cerr << "Entered hyper period is not an integer" << std::endl;
			}
		}

		// all arguments tests have passed -> do the generation
		std::cout << "Generate system with " << tasks << " tasks, " 
			<< utilization_factor << "% utilization " 
			<< "and " << hyper_period << " as semi-maximal hyper period "
			<< "to file: " << args[6] 
			<< std::endl;
		
		RandomSystem rs(tasks, utilization_factor, 2000);

		std::vector<Task> tasks = rs.get_tasks();

		display_tasks(tasks);
		std::cout << "total U : " << total_utilization(tasks) * 100  << std::endl;
		
		// now write the tasks to file
		write_tasks_to_file(tasks, args[6]);

		return 0;
	}

	show_task_generation_usage(argv[0]);
	
	return 1;
}
