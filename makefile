all: zadatak
zadatak: zadatak.o
	gcc -o zadatak zadatak.o
zadatak.o : zadatak.c
	gcc -c zadatak.c
clean:
	rm zadatak.o zadatak
