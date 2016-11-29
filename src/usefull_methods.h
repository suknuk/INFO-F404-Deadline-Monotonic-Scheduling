#ifndef USEFULL_METHODS_H
#define USEFULL_METHODS_H

#include <vector>
#include "task.h"

// Displaying text on how to use the program
void show_usage(char* argv0);

// Checking if argument is -p or -g
bool is_arg_p_or_g(char* argv, bool &type);

// checking if a file exists
bool does_file_exist(char* argv, std::string *file_name);

// checking if a char* is a number
bool is_number(char* argv, int* number);

// reading file to return a vector of tasks
std::vector<Task> read_tasks_file(char* file_name);

// Simple check of total utilization vs # processors
double total_utilization(std::vector<Task> &tasks);

// Calculate gcd of 2 numbers 
int gcd(int a, int b);

// Calculate lcm of 2 numbers
int lcm(int a, int b);

// Calculate the interval I = [0; max_offset + 2* hyper_period] -- p = lcm
int interval(std::vector<Task> &tasks);

// Simple output of the scheduling
void display_scheduling(std::vector <std::vector<Task *> > &schedule, std::vector<Task> &tasks);

#endif
