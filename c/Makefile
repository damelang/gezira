CFLAGS := -Wall -Wno-unused -O2 

default: main

nile.o: nile.h nile.c
	gcc -c $(CFLAGS) nile.c

gezira.o: nile.h gezira.h gezira.c
	gcc -c $(CFLAGS) -mfpmath=sse -ffast-math gezira.c

main: nile.o gezira.o main.c
	gcc $(CFLAGS) main.c -o main nile.o gezira.o

clean:
	/bin/rm -rf main *.o
