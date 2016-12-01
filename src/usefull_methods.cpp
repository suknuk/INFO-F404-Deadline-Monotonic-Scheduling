#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <map>
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


bool is_arg_p_or_g(char* argv, bool &type)
{
	std::string arg (argv);
	std::string p ("-p");
	std::string g ("-g");
 
	if (p.compare(arg) == 0) { 
		type = false;
	} else if (g.compare(arg) == 0) {
		type = true;
	} else {
		return false;
	}
	return true;
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

double total_utilization(std::vector<Task> &tasks)
{
	double total_utilization = 0;
			
	for (unsigned i = 0; i < tasks.size(); i++) {
		total_utilization += tasks[i].calculate_utilization();
	}

	return total_utilization;
}

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b,a%b);
}

int lcm(int a, int b)
{
	return a * (b / gcd(a, b));
}

int interval(std::vector<Task> &tasks)
{
	if (tasks.empty()){
		return 0;
	}
	
	int max_offset = 0;
	int period = tasks[0].get_period();

	for (unsigned i = 0; i < tasks.size(); i++) {
		// Find the maximum offset
		if (tasks[i].get_offset() > max_offset) { max_offset=tasks[i].get_offset(); }
		// Calculate the lcm
		if (i+1 < tasks.size()){
			period = lcm(period, tasks[i+1].get_period());
		}
	}

	return max_offset + 2 * period;
}


void display_scheduling(std::vector <std::vector<Task *> > &schedule, std::vector<Task> &tasks)
{
	//map of all tasks in order
	std::map<Task *, int> priority;

	for (unsigned i = 0; i < tasks.size(); i++) {
		priority[&tasks[i]] = i + 1;
	}

	for (unsigned y = 0; y < schedule.size(); y++) {
		for (unsigned x = 0; x < schedule[y].size(); x++) {
			if (NULL == schedule[y][x]) {
				std::cout << std::setw(3) << "_";
			} else {
				// print priority of task
				std::cout << std::setw(3) << priority.at(schedule[y][x]);
			}
		}
		std::cout << std::endl;
	}
}







