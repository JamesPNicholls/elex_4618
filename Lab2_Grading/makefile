all: main

main: main.o CCourse.o
	g++ main.o CCourse.o -o main

main.o: main.cpp
	g++ -c main.cpp

CCourse.o: CCourse.cpp
	g++ -c CCourse.cpp

Clean:
	rm *o main


	