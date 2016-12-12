#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "usefull_methods.h"

void show_study_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " <SystemFile> <OutputFile>\n"
		<< "\t <SystemFile>\tPath to file that describes the to be studied system\n"
		<< "\t <OutputFile>\tPath to file in which the results will be stored"
		<< std::endl;

}

int main(int argc, char* argv[])
{

	// right # of args?
	if (argc != 3) {
		//show_study_usage(argv[0]);
		//return 1;
	}
	// input file exists?
//	else if(!does_file_exist(argv[1], &input_file)) {
//		std::cerr << argv[1] << "cannot be opened" << std::endl;
//	}
	else {

		// how many tasks settings
		int tasks_descriptions;
		// how many U settings
		int utilization_descriptions;

		// hols the info
		std::vector<int> task_nr;
		std::vector<int> utilization_nr;

		// read system file
		std::ifstream input(argv[1]);
		if (input) {
			std::string line;


			// get tasks number
			std::getline(input, line);
			std::stringstream t_nr(line);
			t_nr >> tasks_descriptions;

			//get u numbers
			std::getline(input, line);
			std::stringstream u_nr(line);
			u_nr >> utilization_descriptions;
			
			// now read all task descriptions
			std::getline(input, line);
			std::stringstream ts(line);
			for (int i = 0; i < tasks_descriptions; i++) {
				int t;
				ts >> t;
				task_nr.push_back(t);
			}

			//read all u descriptions
			std::getline(input, line);
			std::stringstream us(line);
			for (int i = 0; i < utilization_descriptions; i++) {
				int u;
				us >> u;
				utilization_nr.push_back(u);
			}

			std::cout << tasks_descriptions << " " << utilization_descriptions << std::endl;

		} else {
			std::cerr << "Could not open input file " << argv[1] << std::endl;
			return 1;
		}
		return 0;
	}
	
	show_study_usage(argv[0]);
	return 1;
}
