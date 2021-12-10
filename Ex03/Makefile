all: testing.o
	gcc -o testing testing.o -lm

testing.o: testing.c
	gcc -c testing.c

clean:
	rm *.o testing