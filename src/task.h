#ifndef TASK_H 
#define TASK_H

class Task 
{
private:
	int offset, period, deadline, wcet;
public:
	Task(int,int,int,int);
	int calculate_utilization();
	
	// getters
	int get_offset() const;
	int get_period() const;
	int get_deadline() const;
	int get_wcet() const;
};

#endif
