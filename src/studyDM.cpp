#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "simulate_global.h"
#include "simulate_partitioned.h"
#include "random_system.h"
#include "prioritySort.h"
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

			// storing the minimum requirements for global vs partitioned
			std::vector<int> req_g;
			std::vector<int> req_p;

			// storing distribution values
			std::vector<double> dist_g;
			std::vector<double> dist_p;

			// now iterate every possibility and save the output
			for (int t = 0; t < tasks_descriptions; t++) {
				for (int u = 0; u < utilization_descriptions; u++) {
					// impossible to generate such a system? i.e. 2 tasks with U = 250%
					// -> set it to -1
					if (task_nr[t]*100 < utilization_nr[u]){
						req_g.push_back(-1);
						req_p.push_back(-1);
						dist_g.push_back(-1);
						dist_p.push_back(-1);
						continue;
					}

					// generate the random system
				
					std::cout << "generate : " << task_nr[t] << " " << utilization_nr[u]
						<< std::endl;
					RandomSystem rs(task_nr[t], utilization_nr[u], 1000 );
						
					std::vector< std::vector<Task*> > gschedule;
					
					std::vector<Task> tasks = rs.get_tasks();
					std::sort(tasks.begin(), tasks.end(), deadlinePriority);

					int processors = ceil(total_utilization(tasks));
					int study_interval = interval(tasks);
					std::vector<int> pre_g;
					
					display_tasks(tasks);

					std::cout << "global starting" << std::endl;
					// all global strategy values
					int req_proc_g = minimum_global_processors_required(tasks, gschedule, 
							processors, study_interval, pre_g);
					req_g.push_back(req_proc_g);
					double global_dist = system_load_distribution(gschedule,tasks, req_proc_g);
					dist_g.push_back(global_dist);

					std::cout << "global done" << std::endl;

					// partitioned strategy
					std::vector<UniprocessorDM> pschedule;
					int req_proc_p = minimum_partitioned_processors_required(tasks,pschedule);
					req_p.push_back(req_proc_p);

					std::vector< std::vector<Task*> > pschedule_v = uniprocessors_to_vector(pschedule, pre_g);
					double partitioned_dist = system_load_distribution(pschedule_v,tasks,req_proc_p);
					dist_p.push_back(partitioned_dist);
					std::cout << "partitioned done" << std::endl;
				}
			}

			std::string output_file(argv[2]);
			std::ofstream out(output_file.c_str());

			for (int i = 0; i < 4; i++) {
				int counter = 0;
				if (i == 0) {
					out << "global scheduling required processors:\n";
				} else if (i == 1) {
					out << "global scheduling distribution load:\n";
				} else if (i == 2) {
					out << "partitioned scheduling required processors:\n";
				} else if(i==3) {
					out << "partitioned scheduling distribution load:\n";
				}
				// write the required processors of each system to file
				for (int t = 0; t < tasks_descriptions; t++) {
					for (int u = 0; u < utilization_descriptions; u++) {
						
						if (i == 0) {
							out << req_g.at(counter) << " ";
						} else if(i == 1) {
							out << dist_g.at(counter) << " ";
						} else if (i == 2) {
							out << req_p.at(counter) << " ";
						} else if(i==3){
							out << dist_p.at(counter) << " ";
						}
						counter++;
					}
					out << '\n';
				}
			}

			out.close();
			
		} else {
			std::cerr << "Could not open input file " << argv[1] << std::endl;
			return 1;
		}
		return 0;
	}
	
	show_study_usage(argv[0]);
	return 1;
}
