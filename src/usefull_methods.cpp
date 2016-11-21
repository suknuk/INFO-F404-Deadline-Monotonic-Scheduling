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


