all: main2.o
	gcc main2.o -o imageresize -ljpeg
	
main.o: main2.c
	gcc -c main2.c
	
clean:
	rm *.o imageresize
