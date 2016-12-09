#include "prioritySort.h"

bool deadlinePriority(const Task &t1, const Task &t2)
{
	// sort by deadline first as it is DM
	if (t1.get_deadline() < t2.get_deadline()){
		return true;
	} else if (t1.get_deadline() > t2.get_deadline()) {
		return false;
	// ow deadlines are equal
	} else {
		// utilization secondly
		if (t1.calculate_utilization() > t2.calculate_utilization()) { 	
			return  true; 
			
		} else if (t1.calculate_utilization() > t2.calculate_utilization()) {
			return false;
		// utilization also equal
		} else {
			//offset thirdly
			if (t1.get_offset() < t2.get_offset()) {
				return true;
			} else if (t1.get_offset() > t2.get_offset()) {
				return false;
			// ow they are equal in deadline, utilization and offset
			} else {
				return true;
			}
		}
	}
}

bool utilizationPriority(const Task &t1, const Task &t2)
{
	// sort by utilization first as it is DM
	if (t1.calculate_utilization() < t2.calculate_utilization()){
		return true;
	} else if (t1.calculate_utilization() > t2.calculate_utilization()) {
		return false;
	// ow utilizations are equal
	} else {
		// sort by deadlines as it is a DM system
		if (t1.get_deadline() < t2.get_deadline()){
			return true;
		} else if (t1.get_deadline() > t2.get_deadline()) {
			return false;
		// ow deadlines are equal
		} else {
			// sort by the offset
			if (t1.get_offset() < t2.get_offset()) {
				return true;
			} else if (t1.get_offset() > t2.get_offset()) {
				return false;
			// ow they are equal in deadline, utilization and offset, so dont change the order
			} else {
				return true;
			}
		}
	}
}
