#include <iostream>
#include <string>

void show_study_usage(char* argv0)
{
	std::cerr << "Usage: " << argv0 << " <SystemFile> <OutputFile>\n"
		<< "\t <SystemFile>\tPath to file that describes the to be studied system\n"
		<< "\t <OutputFile>\tPath to file in which the results will be stored"
		<< std::endl;

}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		show_study_usage(argv[0]);
		return 1;
	}
	std::cout << "hello world" << std::endl;
	return 0;
}
