NILE_RUNTIME := ../../nile/runtimes/c
CFLAGS       := -O2 -Wall -Werror -Wno-unused \
                -mfpmath=sse -ffast-math -fstrict-aliasing -I$(NILE_RUNTIME)

libgezira.a: gezira.o gezira-image.o
	ar rcs $@ $^

clean:
	$(RM) *.o *.a
