all: ex04task04.o stopwatch.o
	g++ -o stopwatch ex04task04.o stopwatch.o

ex04task04.o: ex04task04.cpp
	g++ -c ex04task04.cpp

stopwatch.o: stopwatch.cpp
	g++ -c stopwatch.cpp

clean:
	rm *.o stopwatch