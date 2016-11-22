#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include "usefull_methods.h"

void show_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " [-g | -p] <tasksFile> <processorsNbr>\n" 
		<< "\t-p\t\tPartitioned scheduling strategy\n"
		<< "\t-g\t\tGlobal scheduling strategy\n"
		<< "\t<tasksFile>\tFile describing the tasks\n"
		<< "\t<processorsNbr>\tNumber of processors contained by the System"
		<< std::endl;
}

bool does_file_exist(char* argv, std::string *file_name)
{
	std::string file(argv);
	std::ifstream f(file.c_str());
	if (f.good()) {
		*file_name = file;
		return true;
	} else {
		return false;
	}
}

bool is_number(char* argv, int* number)
{
	std::istringstream ss(argv);
	if (!((ss >> *number) && (ss.eof()))) {
		return false; 
	}
	return true;
}

std::vector<Task> read_tasks_file(char* file_name)
{
	std::vector<Task> tasks;
	
	std::ifstream file(file_name);
	if (!file) {
		std::cerr << "Failed to open " << file_name << std::endl;
		return tasks;
	}

	int offset, period, deadline, wcet;
	std::string line;
	// Read until no more tasks are left
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		ss >> offset >> period >> deadline >> wcet;
		Task task(offset, period, deadline, wcet);
		tasks.push_back(task);
	}
	
	return tasks;
}
