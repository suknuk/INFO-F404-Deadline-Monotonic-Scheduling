CC = g++
CFLAGS = -c -Wall -Wextra

all: simDM

simDM: simDM.o usefull_methods.o task.o simulate_global.o
	$(CC) simDM.o usefull_methods.o task.o simulate_global.o -o simDM

simDM.o: src/simDM.cpp
	$(CC) $(CFLAGS) src/simDM.cpp

usefull_methods.o: src/usefull_methods.cpp
	$(CC) $(CFLAGS) src/usefull_methods.cpp

task.o: src/task.cpp
	$(CC) $(CFLAGS) src/task.cpp

simulate_global.o: src/simulate_global.cpp
	$(CC) $(CFLAGS) src/simulate_global.cpp

clean: 
	rm *.o simDM
