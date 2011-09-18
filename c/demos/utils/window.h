#ifndef GEZIRA_WINDOW_H
#define GEZIRA_WINDOW_H

typedef struct gezira_Window_ gezira_Window_t;

typedef struct {
    gezira_Window_t *window;
} gezira_WindowUpdate_vars_t;

#ifdef GEZIRA_WINDOW_NONE

struct gezira_Window_ {
    int           width;
    int           height;
    uint32_t     *pixels;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    window->width = width;
    window->height = height;
    window->pixels = malloc (width * height * sizeof (uint32_t));
}

static char
gezira_Window_key_pressed (gezira_Window_t *window)
    { return -1; }

static void
gezira_Window_fini (gezira_Window_t *window)
    { free (window->pixels); }

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
    { return out; }

#elif defined(__APPLE__)

#include <ApplicationServices/ApplicationServices.h>
#include <objc/objc-runtime.h>
#define NSBorderlessWindowMask                       0
#define NSTitledWindowMask                           1
#define NSBackingStoreBuffered                       2
#define NSAnyEventMask                       ULONG_MAX
#define NSKeyDown                                   10
#define NSApplicationActivationPolicyRegular         0
typedef long NSEventType;
extern void* const NSDefaultRunLoopMode;

struct gezira_Window_ {
    int           width;
    int           height;
    uint32_t     *pixels;
    id            pool;
    id            NSApp;
    id            nswindow;
    CGContextRef  context;
    CGContextRef  bitmap;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height, int x, int y)
{
    id nscontext;
    CGColorSpaceRef colorspace;
    window->width = width;
    window->height = height;
    window->pixels = malloc (width * height * sizeof (uint32_t));

    /* NSApp */
    window->NSApp = objc_msgSend (objc_getClass ("NSApplication"), sel_getUid ("sharedApplication"));
    window->pool = objc_msgSend (objc_getClass ("NSAutoreleasePool"), sel_getUid ("alloc"));
    objc_msgSend (window->pool, sel_getUid ("init"));
    if (objc_msgSend (window->NSApp, sel_getUid ("respondsToSelector:"), sel_getUid("setActivationPolicy:")))
        objc_msgSend (window->NSApp, sel_getUid ("setActivationPolicy:"), NSApplicationActivationPolicyRegular);
    objc_msgSend (window->NSApp, sel_getUid ("activateIgnoringOtherApps:"), YES);

    /* NSWindow */
    window->nswindow = objc_msgSend (objc_getClass ("NSWindow"), sel_getUid ("alloc"));
    objc_msgSend (window->nswindow, sel_getUid ("initWithContentRect:styleMask:backing:defer:"),
        CGRectMake (x, y, width, height),
        NSBorderlessWindowMask, NSBackingStoreBuffered, NO);
    objc_msgSend (window->nswindow, sel_getUid ("makeKeyAndOrderFront:"), window->NSApp);
    objc_msgSend (window->nswindow, sel_getUid ("setLevel:"), 1000);

    /* CGContexts */
    nscontext = objc_msgSend (objc_getClass ("NSGraphicsContext"), sel_getUid ("currentContext"));
    window->context = (CGContextRef) objc_msgSend (nscontext, sel_getUid ("graphicsPort"));
    colorspace = CGColorSpaceCreateDeviceRGB ();
    window->bitmap = CGBitmapContextCreate (window->pixels, width, height, 8, width * 4, colorspace,
                                            kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host);
    CGColorSpaceRelease (colorspace);
    CGContextSetBlendMode (window->context, kCGBlendModeCopy);
    CGContextSetRenderingIntent (window->context, kCGRenderingIntentAbsoluteColorimetric);
}

static char
gezira_Window_key_pressed (gezira_Window_t *window)
{
    id now = objc_msgSend (objc_getClass ("NSDate"), sel_getUid ("date"));
    id event = objc_msgSend (window->NSApp, sel_getUid ("nextEventMatchingMask:untilDate:inMode:dequeue:"),
                             NSAnyEventMask, now, NSDefaultRunLoopMode, YES);
    if (event) {
        NSEventType type = (NSEventType) objc_msgSend (event, sel_getUid ("type"));
        if (type == NSKeyDown) {
            id nsstring = objc_msgSend (event, sel_getUid ("characters"));
            const char *cstring = (const char *) objc_msgSend (nsstring, sel_getUid ("UTF8String"));
            return cstring[0];
        }
    }
    return -1;
}

static void
gezira_Window_fini (gezira_Window_t *window)
{
    CGContextRelease (window->bitmap);
    CGContextRelease (window->context);
    objc_msgSend (window->nswindow, sel_getUid ("close"));
    objc_msgSend (window->pool, sel_getUid ("release"));
    free (window->pixels);
}

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Window_t *window = *((gezira_Window_t **) nile_Process_vars (p));
    CGImageRef image = CGBitmapContextCreateImage (window->bitmap);
    CGContextDrawImage (window->context, CGRectMake (0, 0, window->width, window->height), image);
    CGImageRelease (image);
    CGContextFlush (window->context);
    return out;
}

#elif defined (_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#error TODO move code over here

#elif defined (__unix__)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct gezira_Window_ {
    int              width;
    int              height;
    uint32_t        *pixels;
    XShmSegmentInfo *segment;
    Display         *display;
    GC               gc;
    XImage          *image;
    Window           x11window;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    int depth;
    Atom atom;
    window->width = width;
    window->height = height;
    window->segment = (XShmSegmentInfo *) malloc (sizeof (XShmSegmentInfo));
    window->display = XOpenDisplay (0);
    window->gc = DefaultGC (window->display, DefaultScreen (window->display));
    depth = XDefaultDepth (window->display, DefaultScreen (window->display));
    if (!(depth == 24 || depth == 32)) {
        fprintf (stderr, "Unsupported display depth: %d\n", depth);
        exit (1);
    }
    window->image = XShmCreateImage (window->display, CopyFromParent, depth, ZPixmap,
                                     NULL, window->segment, width, height);
    window->x11window = XCreateWindow (window->display, DefaultRootWindow (window->display),
                                       50, 50, width, height, 0, depth, InputOutput,
                                       CopyFromParent, 0, NULL);
    window->segment->shmid = shmget (IPC_PRIVATE, window->image->bytes_per_line * height,
                                     IPC_CREAT | 0777);
    window->segment->shmaddr = window->image->data =
        (char *) shmat (window->segment->shmid, 0, 0);
    window->pixels = (uint32_t *) window->image->data;
    window->segment->readOnly = True;
    XShmAttach (window->display, window->segment);
    shmctl (window->segment->shmid, IPC_RMID, NULL);
    atom = XInternAtom (window->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (window->display, window->x11window, &atom, 1);
    XMapWindow (window->display, window->x11window);
    XSync (window->display, True);
}

static void
gezira_Window_fini (gezira_Window_t *window)
{
    XShmDetach (window->display, window->segment);
    XDestroyImage (window->image);
    shmdt (window->segment->shmaddr);
    free (window->segment);
    XDestroyWindow (window->display, window->x11window);
    XCloseDisplay (window->display);
}

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Window_t *window = *((gezira_Window_t **) nile_Process_vars (p));
    XShmPutImage (window->display, window->x11window, window->gc, window->image, 0, 0, 0, 0,
                  window->image->width, window->image->height, False);
    XSync (window->display, False);
    return out;
}

#else
#error Unsupported platform!
#endif

static nile_Process_t *
gezira_WindowUpdate (nile_Process_t *p, gezira_Window_t *window)
{
    p = nile_Process (p, 1, sizeof (gezira_WindowUpdate_vars_t),
                      gezira_WindowUpdate_prologue, NULL, NULL);
    if (p) {
        gezira_WindowUpdate_vars_t *vars = nile_Process_vars (p);
        vars->window = window;
    }
    return p;
}

static nile_Process_t *
gezira_Window_update_and_clear (gezira_Window_t *window, nile_Process_t *init, nile_Process_t *gate,
                                float a, float r, float g, float b)
{
    nile_Process_t *gate_ = nile_Identity (init, 1);
    nile_Process_t *clear = gezira_CompositeUniformColorOverImage_ARGB32 (init,
        a, r, g, b,
        window->pixels, window->width, window->height, window->width);
    nile_Process_gate (clear, gate_);
    nile_Process_feed (nile_Process_pipe (
        gate,
        gezira_WindowUpdate (init, window),
        gezira_RectangleSpans (init, 0, 0, window->width, window->height),
        clear,
        NILE_NULL),
        NULL, 0);
    return gate_;
}

#endif
