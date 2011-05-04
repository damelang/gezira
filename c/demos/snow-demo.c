#include <stdlib.h>
#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
#include "utils/snowflake.h"
#include "utils/matrix.h"
#include "utils/window.h"

#define MEM_SIZE 20000000
#define NTHREADS 1
#define DEFAULT_WIDTH  600
#define DEFAULT_HEIGHT 600
//#define NFLAKES 500
#define NFLAKES 1000
#define NFRAMES_PER_FPS_UPDATE 50

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
    float x, y, dy, scale, rotation, angle, alpha, red, green, blue;
} gezira_snowflake_t;

static void
update_flake (gezira_snowflake_t *flake)
{
    flake->y += flake->dy;
    flake->angle += flake->rotation;
    if (flake->y > DEFAULT_HEIGHT + 10)
        flake->y = -10;
}

static float zoomX = 1;
static float zoomY = 1;
static float zoomD = 0.01;

static void
render_flake (gezira_snowflake_t *flake, nile_Process_t *init, nile_Process_t *COI)
{
    Matrix_t M = Matrix ();
    M = Matrix_translate (M, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / 2);
    M = Matrix_scale (M, zoomX, zoomY);
    M = Matrix_translate (M, -DEFAULT_WIDTH / 2, -DEFAULT_HEIGHT / 2);
    M = Matrix_translate (M, flake->x, flake->y);
    M = Matrix_rotate (M, flake->angle);
    M = Matrix_scale (M, flake->scale, flake->scale);

    nile_Process_t *p = nile_Process_pipe (
        nile_Funnel (init),
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (init),
        COI,
        NILE_NULL);
    nile_Funnel_pour (p, snowflake_path, snowflake_path_n, 1);
}

void 
nile_pour (nile_Process_t *init, nile_Process_t *p, float *data, int n)
{
    nile_Funnel_pour (nile_Process_pipe (nile_Funnel (init), p, NILE_NULL), data, n, 1);
}

int
main (int argc, char **argv)
{
    int i;
    double before;
    int frames = 0;
    nile_Process_t *init, *COI, *clear;
    gezira_snowflake_t flakes[NFLAKES];
    int zoom = 0;
    gezira_Window_t window;
    char *mem = malloc (MEM_SIZE);

    init = nile_startup (mem, MEM_SIZE, NTHREADS);
    if (!init) {
        fprintf (stderr, "nile_startup failed\n");
        exit (1);
    }

    gezira_Window_init (&window, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    echo (0);

    srand (17837643);
    for (i = 0; i < NFLAKES; i++) {
        flakes[i].x = rand_upto (window.width);
        flakes[i].y = rand_upto (window.height);
        flakes[i].dy = 0.5 + rand_upto (2.5);
        flakes[i].scale = 0.2 + rand_upto (0.5);
        //flakes[i].scale = 0.1 + rand_upto (0.4);
        flakes[i].rotation = 0.1 - rand_upto (0.2);
        flakes[i].angle = rand_upto (3);
        flakes[i].alpha = 0.7;
        flakes[i].red = 0.8;
        flakes[i].green = 0.9;
        flakes[i].blue = 1.0;
    }

    before = gettimeofday_d ();

    clear = gezira_CompositeUniformColorOverImage_ARGB32 (init, 1, 0, 0, 0,
                window.pixels, window.width, window.height, window.width);
    COI = gezira_CompositeUniformColorOverImage_ARGB32 (init,
            flakes[0].alpha, flakes[0].red, flakes[0].green, flakes[0].blue,
            window.pixels, window.width, window.height, window.width);
    nile_Process_gate (clear, COI);
    nile_pour (init, nile_Process_pipe (
        gezira_RectangleSpans (init, 0, 0, window.width, window.height), clear, NILE_NULL),
        NULL, 0);

    for (;;) {
        char c = inputChar ();
        if (c) {
            int nthreads = c - '0';
            if (!nthreads)
                break;
            switch (c) {
                case ')': nthreads = 10; break;
                case '!': nthreads = 11; break;
                case '@': nthreads = 12; break;
                case '#': nthreads = 13; break;
                case '$': nthreads = 14; break;
                case '%': nthreads = 15; break;
                case '^': nthreads = 16; break;
                case '&': nthreads = 17; break;
                case '*': nthreads = 18; break;
                case '(': nthreads = 19; break;
                case 'z': zoom = !zoom;  break;
                default: break;
            }
            if (nthreads < 0 || nthreads > 50)
                printf ("invalid thread count\n");
            else {
                printf ("%d threads\n", nthreads); fflush (stdout);
                nile_pour (init, COI, NULL, 0);
                nile_sync (init);
                nile_shutdown (init);
                init = nile_startup (mem, MEM_SIZE, nthreads);
                COI = gezira_CompositeUniformColorOverImage_ARGB32 (init,
                        flakes[0].alpha, flakes[0].red, flakes[0].green, flakes[0].blue,
                        window.pixels, window.width, window.height, window.width);
            }
        }

        for (i = 0; i < NFLAKES; i++) {
            int j = (i + 1) % NFLAKES;
            nile_Process_t *COI_ = gezira_CompositeUniformColorOverImage_ARGB32 (init,
                flakes[j].alpha, flakes[j].red, flakes[j].green, flakes[j].blue,
                window.pixels, window.width, window.height, window.width);
            if (j != 0) {
                nile_Process_gate (COI, COI_);
                render_flake (&flakes[i], init, COI);
            }
            else {
                clear = gezira_CompositeUniformColorOverImage_ARGB32 (init,
                       1, 0, 0, 0, window.pixels, window.width, window.height, window.width);
                nile_Process_gate (clear, COI_);
                render_flake (&flakes[i], init, nile_Process_pipe (
                    COI,
                    gezira_WindowUpdate (init, &window),
                    gezira_RectangleSpans (init, 0, 0, window.width, window.height),
                    clear,
                    NILE_NULL));
            }
            COI = COI_;
            update_flake (&flakes[i]);
        }

        if (zoom) {
            zoomX += zoomD;
            zoomY += zoomD;
            if (zoomX > 3 || zoomX < 1 - zoomD)
                zoomD = -zoomD;
        }
        frames++;
        if (!(frames % NFRAMES_PER_FPS_UPDATE)) {
            /*
            nile_sync (init);
            if (nile_error (init)) {
                fprintf (stderr, "nile_error!\n");
                nile_print_leaks (init);
                break;
            }
            nile_print_leaks (init);
            */
            double now = gettimeofday_d ();
            printf ("fps: %.1lf\n", NFRAMES_PER_FPS_UPDATE / (now - before));
            before = now;
        }
    }

    nile_pour (init, COI, NULL, 0);
    nile_sync (init);
    nile_shutdown (init);
    free (mem);
    gezira_Window_fini (&window);
    echo (1); // todo use atexit
    printf ("frames: %d\n", frames);

    return 0;
}
