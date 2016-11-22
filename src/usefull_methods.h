#ifndef USEFULL_METHODS_H
#define USEFULL_METHODS_H

#include <vector>
#include "task.h"

// Displaying text on how to use the program
void show_usage(char* argv0);

// checking if a file exists
bool does_file_exist(char* argv, std::string *file_name);

// checking if a char* is a number
bool is_number(char* argv, int* number);

// reading file to return a vector of tasks
std::vector<Task> read_tasks_file(char* file_name);

#endif
