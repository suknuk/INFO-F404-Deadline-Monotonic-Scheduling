#ifndef USEFULL_METHODS_H
#define USEFULL_METHODS_H

#include <vector>
#include <map>
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

// total utilization from Task* vector
double total_utilization(std::vector<Task*> &tasks);

// Simple check of total utilization vs # processors
double total_utilization(std::vector<Task> &tasks);

// Calculate gcd of 2 numbers 
int gcd(int a, int b);

// Calculate lcm of 2 numbers
int lcm(int a, int b);

// Calculate interval overload
int interval(std::vector<Task*> &tasks);

// Calculate the interval I = [0; max_offset + 2* hyper_period] -- p = lcm
int interval(std::vector<Task> &tasks);

// displaying tasks information
void display_tasks(std::vector<Task> &tasks);

// Simple output of the scheduling
void display_scheduling(std::vector <std::vector<Task *> > &schedule);

// Calculate idle time of a single processor
int processor_idle_time(std::vector<Task*> &schedule);

// Calculate idle percentage time of single processor
double processor_idle_percentage(std::vector<Task*> &schedule);

// Calculate the total idle time of a system
int system_idle_time(std::vector< std::vector<Task*> > &schedule);

// System idle time in %
double system_idle_percentage(std::vector< std::vector<Task*> > &schedule);

#endif
