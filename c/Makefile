NILE_RUNTIME := ../../nile/runtimes/c
CFLAGS       := -O2 -Wall -Werror -Wno-unused \
                -mfpmath=sse -ffast-math -fstrict-aliasing -I$(NILE_RUNTIME)
LIBS         := -L. -lgezira -L$(NILE_RUNTIME) -lnile

ifeq ($(findstring exe,$(SHELL)),)
  CFLAGS += $(shell sdl-config --cflags 2>/dev/null || \
              echo -I/Library/Frameworks/SDL.framework/Headers)
  LIBS   += $(shell sdl-config --libs 2>/dev/null || \
              echo -framework SDL -framework Cocoa SDLMain.m)
else
  ifeq ($(SDL_DIR),)
    $(error Must set SDL_DIR environment variable (e.g., ../../SDL-1.2.14.mingw32))
  else
    CFLAGS += -I$(SDL_DIR)/include/SDL
    LIBS   += -L$(SDL_DIR)/lib -lSDL -mwindows
  endif
endif

libgezira.a: gezira.o gezira-image.o
	ar rcs $@ $^

%-demo: %-demo.c libgezira.a
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o *.a *-demo
