#ifndef GEZIRA_FPS_H
#define GEZIRA_FPS_H

#include <stdio.h>

#define FPS_CAP 60

#if defined(__unix__) || defined(__APPLE__)
#include <sys/time.h>
static double
gezira_gettime ()
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static double
gezira_gettime ()
{
    LARGE_INTEGER counter, frequency;
    QueryPerformanceFrequency (&frequency);
    QueryPerformanceCounter (&counter);
    return (double) counter.QuadPart / frequency.QuadPart;
}
#else
#error Unsupported platform!
#endif

static void
gezira_update_fps (nile_Process_t *init)
{
    static double before = -1;
    double now = gezira_gettime ();
    double fps = 1 / (now - before);
    if (before < 0) {
        before = now;
        return;
    }
    if (fps > FPS_CAP) {
        nile_sync (init);
        now = gezira_gettime ();
        fps = 1 / (now - before);
    }
    if (floor (before) < floor (now))
        printf ("FPS: %.1lf (capped at %d FPS)\n", fps, FPS_CAP);
    before = now;
}

#endif
