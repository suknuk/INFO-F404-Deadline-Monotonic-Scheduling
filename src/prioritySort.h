#ifndef PRIORITYSORT_H
#define PRIORITYSORT_H
#include "task.h"

/*
 Sorting based on shorter deadline
 Used for global scheduling and sorting the selected tasks in a uniprocessor
*/ 
bool deadlinePriority(const Task &t1, const Task &t2);

// pointing to previous method by converting the pointers
bool deadlinePriorityPointers(const Task *t1, const Task *t2);

/*
 Sorting based on utilization
 Used for 'bin packing' for partitioned scheduling to assign tasks intially to the processors
*/
bool utilizationPriority(const Task &t1, const Task &t2);

#endif
