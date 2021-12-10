all: main.o
	gcc main.o -o imagecopy -ljpeg
	
main.o: main.c
	gcc -c main.c
	
clean:
	rm *.o imagecopy
