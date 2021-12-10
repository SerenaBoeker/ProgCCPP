all: main.o
	gcc main.o -o proportional -ljpeg
	
main.o: main.c
	gcc -c main.c
	
clean:
	rm *.o proportional
