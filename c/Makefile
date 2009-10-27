CFLAGS := -Wall -Wno-unused -O2 -mfpmath=sse -ffast-math -fstrict-aliasing

default: main

nile.o: nile.h nile.c
	gcc -c $(CFLAGS) nile.c

gezira.o: nile.h gezira.h gezira.c
	gcc -c $(CFLAGS) gezira.c

main: nile.o gezira.o main.c
	gcc -o main $(CFLAGS) main.c nile.o gezira.o

clean:
	/bin/rm -rf main *.o *.gch
