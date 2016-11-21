#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>

static void show_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " [-g | -p] <tasksFile> <processorsNbr>\n" 
		<< "\t-p\t\tPartitioned scheduling strategy\n"
		<< "\t-g\t\tGlobal scheduling strategy\n"
		<< "\t<tasksFile>\tFile describing the tasks\n"
		<< "\t<processorsNbr>\tNumber of processors contained by the System"
		<< std::endl;
}

inline bool does_file_exist(char* file_name)
{
	std::string file(file_name);
	std::ifstream f(file.c_str());
	return f.good();
}

inline bool is_number(char* argv)
{
	int number;
	std::istringstream ss(argv);
	if (!((ss >> number) && (ss.eof()))) {
		return false; 
	}
	return true;
}

int main(int argc, char* argv[])
{
	int processors;

	// Checking argument input size
	if (argc < 4 || argc > 5) {
		std::cerr << "Wrong number of arguments!" << std::endl;
	}
	// Checking -p | -g
	else if (!(strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-g") == 0)) {
		std::cerr << "Unrecognized argument " << argv[1] << std::endl;
	} 
	// Checking tasks file
	else if (!does_file_exist(argv[2])){
		std::cerr << argv[2] << " cannot be opened" << std::endl;
	}
	// Checking if <processorsNbr> is a integer
	else if (!is_number(argv[3]))
	{
		std::cerr << "Number of processors must be a integer" << std::endl;		
	}
	else 
	{
		std::cout << "Valid input!" << std::endl;
		return 0;
	}
	
	
	show_usage(argv[0]);
	return 1;
}
