NILE_RUNTIME := ../../nile/runtimes/c
CFLAGS := -O2 -Wall -Werror -Wno-unused -mfpmath=sse -ffast-math -fstrict-aliasing \
          -L$(NILE_RUNTIME) -I$(NILE_RUNTIME)
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LIBS := $(shell sdl-config --libs)

demo: demo.c gezira-sdl.o gezira.o
	gcc -o $@ $(CFLAGS) $(SDL_CFLAGS) $^ $(SDL_LIBS) -lnile

%.o: %.c *.h $(MAKEFILE_LIST)
	gcc -c $(CFLAGS) $<

gezira-sdl.o: gezira-sdl.c *.h $(MAKEFILE_LIST)
	gcc -c $(CFLAGS) $(SDL_CFLAGS) $<

clean:
	/bin/rm -rf demo *.o *.a *.gch
