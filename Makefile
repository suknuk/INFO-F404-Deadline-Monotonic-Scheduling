CC = g++

all: simDM

simDM: simDM.o usefull_methods.o task.o
	$(CC) simDM.o usefull_methods.o task.o -o simDM

simDM.o: src/simDM.cpp
	$(CC) -c src/simDM.cpp

usefull_methods.o: src/usefull_methods.cpp
	$(CC) -c src/usefull_methods.cpp

task.o: src/task.cpp
	$(CC) -c src/task.cpp

clean: 
	rm *.o simDM
