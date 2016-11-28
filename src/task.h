#ifndef TASK_H 
#define TASK_H

class Task 
{
private:
	int offset, period, deadline, wcet, priority;
public:
	Task(int,int,int,int);
	double calculate_utilization() const;
	
	// getters
	int get_offset() const;
	int get_period() const;
	int get_deadline() const;
	int get_wcet() const;

};

// overloading the comparison operator so we can sort 
// Task items in a vector
bool operator<(const Task &t1, const Task &t2);

#endif
