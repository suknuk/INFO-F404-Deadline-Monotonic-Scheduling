#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
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
			//std::vector< std::vector<RandomSystem> > system;

			std::vector< std::vector<Task*> > schedule;
			std::vector<Task> tasks;

			// storing the minimum requirements for global vs partitioned
			std::vector<int> req_g;
			std::vector<int> req_p;

			// now iterate every possibility and save the output
			for (int t = 0; t < tasks_descriptions; t++) {
				for (int u = 0; u < utilization_descriptions; u++) {
					// generate the random system
					RandomSystem rs(task_nr[t], utilization_nr[u], 20000 );
					
					tasks = rs.get_tasks();
					int processors = ceil(total_utilization(tasks));
					int study_interval = interval(tasks);
					
					req_g.push_back(minimum_global_processors_required(tasks, schedule, 
							processors, study_interval));
					std::vector<UniprocessorDM> pschedule;
					req_p.push_back(minimum_partitioned_processors_required(tasks,pschedule));
					
					std::cout << t << " " <<  u  << std::endl;
				}
			}

			// write the required processors of each system to file
			for (int t = 0; t < tasks_descriptions; t++) {
				for (int u = 0; u < utilization_descriptions; u++) {
					
				}
			}


		} else {
			std::cerr << "Could not open input file " << argv[1] << std::endl;
			return 1;
		}
		return 0;
	}
	
	show_study_usage(argv[0]);
	return 1;
}
