NILE_RUNTIME := ../../nile/runtimes/c
CFLAGS := -O2 -Wall -Werror -Wno-unused -mfpmath=sse -ffast-math -fstrict-aliasing \
          -L$(NILE_RUNTIME) -I$(NILE_RUNTIME)
SDL_CFLAGS := $(shell sdl-config --cflags 2>/dev/null || \
                echo -I/Library/Frameworks/SDL.framework/Headers)
SDL_LIBS := $(shell sdl-config --libs 2>/dev/null || \
              echo -framework SDL -framework Cocoa SDLMain.m)

demo: demo.c gezira-image.o gezira.o
	$(CC) -o $@ $(CFLAGS) $(SDL_CFLAGS) $^ $(SDL_LIBS) -lnile

%.o: %.c *.h $(MAKEFILE_LIST)
	$(CC) -c $(CFLAGS) $<

clean:
	/bin/rm -rf demo *.o *.a *.gch *.dSYM
