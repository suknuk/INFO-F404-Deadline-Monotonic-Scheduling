#include <iostream>

static void show_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " [-g | -p] <tasksFile> <processorsNbr>\n" 
		<< "\t-p\t\tPartitioned scheduling strategy\n"
		<< "\t-g\t\tGlobal scheduling strategy\n"
		<< "\t<tasksFile>\tFile describing the tasks\n"
		<< "\t<processorsNbr>\tNumber of processors contained by the System"
		<< std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 4 || argc > 5) {
		show_usage(argv[0]);
		return 1;
	}

	return 0;
}
