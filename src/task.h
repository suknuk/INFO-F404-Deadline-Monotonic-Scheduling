#ifndef TASK_H 
#define TASK_H

extern int UID_counter;

class Task 
{
private:
	int offset, period, deadline, wcet, priority, uid;
public:
	Task(int,int,int,int);
	double calculate_utilization() const;
	
	// getters
	int get_offset() const;
	int get_period() const;
	int get_deadline() const;
	int get_wcet() const;
	int get_uid() const;

	// setter
	void set_deadline(int deadline);
	void set_wcet(int wcet);

};

// overloading the comparison operator so we can sort 
// Task items in a vector
bool operator<(const Task &t1, const Task &t2);

#endif
