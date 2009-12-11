CFLAGS := -Wall -Wno-unused -O2 -mfpmath=sse -ffast-math -fstrict-aliasing
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LIBS := $(shell sdl-config --libs)

default: main

nile.o: nile.h nile.c
	gcc -c $(CFLAGS) nile.c

gezira.o: nile.h gezira.h gezira.c
	gcc -c $(CFLAGS) gezira.c

gezira-sdl.o: nile.h gezira.h gezira-sdl.h gezira-sdl.c
	gcc -c $(CFLAGS) $(SDL_CFLAGS) gezira-sdl.c

main: nile.o gezira.o gezira-sdl.o main.c
	gcc -o main $(CFLAGS) $(SDL_CFLAGS) main.c nile.o gezira.o gezira-sdl.o $(SDL_LIBS)

clean:
	/bin/rm -rf main *.o *.gch
