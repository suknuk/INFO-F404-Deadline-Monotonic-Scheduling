#ifndef RANDOM_SYSTEM_H 
#define RANDOM_SYSTEM_H

class RandomSystem
{
	private:
		int _tasks, _utilization;
		void generate_system();
	public:
		RandomSystem(int,int);

};

#endif
