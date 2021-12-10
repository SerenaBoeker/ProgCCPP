all: main3.o
	gcc -g main3.o -o bilinear -ljpeg
	
main.o: main3.c
	gcc -c main3.c
	
clean:
	rm *.o bilinear
