#include <iostream>
#include <string>
#include <sstream>

bool is_number(char* argv, int* number)
{
	std::istringstream ss(argv);
	if (!((ss >> *number) && (ss.eof()))) {
		return false; 
	}
	return true;
}

int main(int argc, char* argv[])
{
	// # of arguments
	if (argc != 7) {
		std::cerr << "Wrong number of arguments!" << std::endl;
		// show_usage
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
	// all arguments tests have passed -> do the generation
	else {
		std::cout << "Generate system with " << tasks << " tasks, " 
			<< utilization_factor << "% utilization " 
			<< "to file: " << args[6] 
			<< std::endl;

		return 0;
	}

	//show_usage
	return 1;
}