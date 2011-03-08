#include <stdlib.h>
#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
//#include "test/nile-print.h"
#include "gezira-matrix.h"
#include "gezira-star-path.h"
#include "Cocoa/Cocoa.h"

#define MEM_SIZE 5000000
#define NTHREADS 1
#define DEFAULT_WIDTH  800
#define DEFAULT_HEIGHT 800
#define NSTARS 500
#define NFRAMES_PER_FPS_UPDATE 50

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

#include <unistd.h>
#include <termios.h>
void echo(bool on) {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  if (on)
    t.c_lflag |= ECHO;
  else
    t.c_lflag &= !ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

bool kbhit(void) {
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return FD_ISSET(0, &fds);
}

int inputChar(void) {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  int c = kbhit() ? getchar() : 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

#include <sys/time.h>
static
double gettimeofday_d ()
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

static float rand_upto (float max) { return rand () / (float) RAND_MAX * max; }

typedef struct {
    float alpha, red, green, blue, x, y, scale, rotation, angle;
} gezira_star_t;

static void
render_star (gezira_star_t *star, nile_Process_t *init, nile_Process_t *WTI)
{
    matrix_t M = matrix_new ();
    M = matrix_translate (M, star->x, star->y);
    M = matrix_rotate (M, star->angle);
    M = matrix_scale (M, star->scale, star->scale);
    M = matrix_translate (M, -250, -250);

    nile_Process_t *p = nile_Process_pipe (
        nile_Funnel (init, 6),
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (init),
        WTI,
        NILE_NULL);
    nile_Funnel_pour (p, star_path, star_path_n, 1);
}

int
main (int argc, char **argv)
{
    uint32_t *pixels = calloc (DEFAULT_WIDTH * DEFAULT_HEIGHT, sizeof (uint32_t));
    nile_Process_t *init;
    char *mem = malloc (MEM_SIZE);
    gezira_star_t stars[NSTARS];
    int i;
    int frames = 0;

    [NSApplication sharedApplication];
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSRect screenFrame = [[NSScreen mainScreen] visibleFrame];
    NSWindow *window = [[NSWindow alloc]
        initWithContentRect: (NSMakeRect (0, screenFrame.size.height, DEFAULT_WIDTH, DEFAULT_HEIGHT))
        styleMask: NSTitledWindowMask | NSClosableWindowMask
        backing: NSBackingStoreBuffered
        defer: NO];
    [window makeKeyAndOrderFront: NSApp];
    NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc]
        initWithBitmapDataPlanes: (unsigned char **) (char *) &pixels
        pixelsWide: DEFAULT_WIDTH
        pixelsHigh: DEFAULT_HEIGHT
        bitsPerSample: 8
        samplesPerPixel: 3
        hasAlpha: NO
        isPlanar: NO
        colorSpaceName: NSDeviceRGBColorSpace
        bytesPerRow: DEFAULT_WIDTH * 4
        bitsPerPixel: 32];

    init = nile_startup (mem, MEM_SIZE, NTHREADS);
    if (!init)
        DIE ("nile_startup failed");

    echo (0);

    srand (17837643);
    for (i = 0; i < NSTARS; i++) {
        stars[i].alpha = rand_upto (1);
        stars[i].red = rand_upto (1);
        stars[i].green = rand_upto (1);
        stars[i].blue = rand_upto (1);
        stars[i].x = rand_upto (DEFAULT_WIDTH);
        stars[i].y = rand_upto (DEFAULT_HEIGHT);
        stars[i].scale = rand_upto (1);
        stars[i].rotation = rand_upto (0.1);
        stars[i].angle = rand_upto (5);
    }

    double before = gettimeofday_d ();

    for (;;) {
        char c = inputChar ();
        if (c) {
            int nthreads = c - '0';
            if (!nthreads)
                break;
            printf ("%d threads\n", nthreads);
            fflush (stdout);
            nile_shutdown (init);
            init = nile_startup (mem, MEM_SIZE, nthreads);
        }

        for (i = 0; i < DEFAULT_HEIGHT * DEFAULT_WIDTH; i++)
            pixels[i] = 0xffffffff;

        nile_Process_t *WTI = gezira_WriteToImage_ARG32_UniformColor (init,
                pixels, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_WIDTH,
                stars[0].alpha, stars[0].red, stars[0].green, stars[0].blue);
        for (i = 0; i < NSTARS - 1; i++) {
            nile_Process_t *WTI_ = gezira_WriteToImage_ARG32_UniformColor (init,
                    pixels, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_WIDTH,
                    stars[i+1].alpha, stars[i+1].red, stars[i+1].green, stars[i+1].blue);
            WTI = nile_Process_gate (WTI, WTI_);
            render_star (&stars[i], init, WTI);
            WTI = WTI_;
            stars[i].angle += stars[i].rotation;
        }
        render_star (&stars[NSTARS - 1], init, WTI);
        stars[NSTARS - 1].angle += stars[NSTARS - 1].rotation;

        if (nile_sync (init)) {
            fprintf (stderr, "sync failed\n");
            break;
        }

        [bitmap drawAtPoint: NSZeroPoint];
        [window flushWindow];
        frames++;

        if (!(frames % NFRAMES_PER_FPS_UPDATE)) {
            double now = gettimeofday_d ();
            printf ("fps: %.2lf\n", NFRAMES_PER_FPS_UPDATE / (now - before));
            before = now;
        }
    }

    /*
    if (nile_sync (init))
        DIE ("sync failed");
        */
    printf ("frames: %d\n", frames);
    free (nile_shutdown (init));
    [pool release];
    free (pixels);
    echo (1); // todo use atexit

    return 0;
}
