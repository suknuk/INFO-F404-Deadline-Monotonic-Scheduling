#include <iostream>
#include <string.h>
#include "usefull_methods.h"

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
	else if (!(strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "-g") == 0)) {
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
		std::string scheduling_type_name;
		if (scheduling_type) {
			scheduling_type_name = "global";
		} else {
			scheduling_type_name = "partitioned";
		}
		std::cout << "Simulating system " << file_name << " in the " 
			<< scheduling_type_name << " strategy with " << processors 
			<< " processors." << std::endl;

		if (scheduling_type) {
			// Simulate global
		} else {
			// Simulate partitioned
		}	

		return 0;
	}
		
	show_usage(argv[0]);
	return 1;
}
