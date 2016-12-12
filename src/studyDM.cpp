#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "simulate_global.h"
#include "simulate_partitioned.h"
#include "random_system.h"
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

			// save all generated systems in vector of vector
			std::vector< std::vector<RandomSystem> > system;

			// now iterate every possibility and save the output
			for (unsigned t = 0; t < task_nr.size(); t++) {
				std::vector<RandomSystem> line;
				system.push_back(line);
				for (unsigned u = 0; u < utilization_nr.size(); u++) {
					// generate the random system
					RandomSystem rs( task_nr[t], utilization_nr[u], 20000 );
					system[t].push_back(rs);
				}
			}

			// simulate each system in global mode
			for (unsigned t = 0; t < task_nr.size(); t++) {
				for (unsigned u = 0; u < utilization_nr.size(); u++) {
						
				}
			}


			std::cout << tasks_descriptions << " " << utilization_descriptions << std::endl;
			std::cout << system.size() << std::endl;

		} else {
			std::cerr << "Could not open input file " << argv[1] << std::endl;
			return 1;
		}
		return 0;
	}
	
	show_study_usage(argv[0]);
	return 1;
}
