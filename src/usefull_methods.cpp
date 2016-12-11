#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
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

double total_utilization(std::vector<Task*> &tasks)
{
	// make vector of tasks instead of *tasks
	std::vector<Task> tmp_tasks;
	for (unsigned i = 0; i < tasks.size(); i++) {
		tmp_tasks.push_back(*tasks[i]);
	}
	return total_utilization(tmp_tasks);
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

int interval(std::vector<Task*> &tasks)
{
	// make vector of tasks instead of *tasks
	std::vector<Task> tmp_tasks;
	for (unsigned i = 0; i < tasks.size(); i++) {
		tmp_tasks.push_back(*tasks[i]);
	}
	return interval(tmp_tasks);
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

void display_tasks(std::vector<Task> &tasks)
{
	std::cout << std::setw(3) << "UID"
		<< std::setw(10)  << "Offset"
		<< std::setw(10)  << "Period"
		<< std::setw(12) << "Deadline"
		<< std::setw(8)  << "WCET"
		<< std::setw(15) << "Utilization"
		<< std::endl;

	for (unsigned i = 0; i < tasks.size(); i++) {
		std::cout << std::setw(3) << tasks[i].get_uid()
			<< std::setw(10)  << tasks[i].get_offset()
			<< std::setw(10)  << tasks[i].get_period()
			<< std::setw(12) << tasks[i].get_deadline()
			<< std::setw(8)  << tasks[i].get_wcet()
			<< std::setw(15) << tasks[i].calculate_utilization()
			<< std::endl;
	}
}


void display_scheduling(std::vector <std::vector<Task *> > &schedule)
{
	for (unsigned processor_nr = 0; processor_nr < schedule.size(); processor_nr++) {
		std::cout << std::setw(6) << "#p" << processor_nr << ":";
		for (unsigned x = 0; x < schedule[processor_nr].size(); x++) {
			if (NULL == schedule[processor_nr][x]) {
				std::cout << std::setw(3) << "_";
			} else {
				// print ID of task
				std::cout << std::setw(3) << schedule[processor_nr][x]->get_uid();
			}
		}
		std::cout << " || Idle time: " << processor_idle_time(schedule[processor_nr])
			<< std::endl;
	}
	std::cout << "Total idle time: " << system_idle_time(schedule) << std::endl;
}

int processor_idle_time(std::vector<Task*> &schedule)
{
	int idle_time = 0;

	for (unsigned i = 0; i < schedule.size(); i++) {
		if (NULL == schedule[i]) {
			idle_time++;
		}
	}

	return idle_time;
}

int system_idle_time(std::vector< std::vector<Task*> > &schedule)
{
	int idle_time = 0;

	for (unsigned i = 0; i < schedule.size(); i++) {
		idle_time += processor_idle_time(schedule[i]);
	}

	return idle_time;
}



