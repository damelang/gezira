CFLAGS := -Wall -O2

default: gezira.o

nile.o: nile.h
	gcc -c $(CFLAGS) nile.c

gezira.o: nile.o gezira.h
	gcc -c $(CFLAGS) -mfpmath=sse -ffast-math gezira.c

main: gezira.o
	gcc $(CFLAGS) main.c -o main nile.o gezira.o

clean:
	/bin/rm -rf main *.o
