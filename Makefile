CC = g++
CFLAGS = -c -Wall -Wextra

all: simDM taskGenerator

simDM: simDM.o usefull_methods.o task.o simulate_global.o simulate_partitioned.o uniprocessorDM.o prioritySort.o pretty_output.o
	$(CC) simDM.o usefull_methods.o task.o simulate_global.o simulate_partitioned.o uniprocessorDM.o prioritySort.o pretty_output.o -o simDM

simDM.o: src/simDM.cpp
	$(CC) $(CFLAGS) src/simDM.cpp

usefull_methods.o: src/usefull_methods.cpp
	$(CC) $(CFLAGS) src/usefull_methods.cpp

task.o: src/task.cpp
	$(CC) $(CFLAGS) src/task.cpp

simulate_global.o: src/simulate_global.cpp
	$(CC) $(CFLAGS) src/simulate_global.cpp

uniprocessorDM.o: src/uniprocessorDM.cpp
	$(CC) $(CFLAGS) src/uniprocessorDM.cpp

simulate_partitioned.o: src/simulate_partitioned.cpp
	$(CC) $(CFLAGS) src/simulate_partitioned.cpp

prioritySort.o: src/prioritySort.cpp
	$(CC) $(CFLAGS) src/prioritySort.cpp

pretty_output.o: src/pretty_output.cpp
	$(CC) $(CFLAGS) src/pretty_output.cpp


taskGenerator: taskGenerator.o random_system.o task.o usefull_methods.o
	$(CC) taskGenerator.o random_system.o task.o usefull_methods.o -o taskGenerator

taskGenerator.o: src/taskGenerator.cpp
	$(CC) $(CFLAGS) src/taskGenerator.cpp

random_system.o: src/random_system.cpp
	$(CC) $(CFLAGS) src/random_system.cpp

clean: 
	rm *.o simDM taskGenerator
