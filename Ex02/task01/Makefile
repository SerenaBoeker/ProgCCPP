all: scope1.o scope2.o
	gcc -o scope scope1.c scope2.c

scope1.o: scope1.c
	gcc -c scope1.c
	
scope2.o: scope2.c
	gcc -c scope2.c

clean:
	rm *.o scope
