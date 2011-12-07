#ifndef GEZIRA_WINDOW_H
#define GEZIRA_WINDOW_H
#include <stdint.h>

typedef struct gezira_Window_ gezira_Window_t;

typedef struct {
    gezira_Window_t *window;
} gezira_WindowUpdate_vars_t;

#ifdef GEZIRA_WINDOW_NONE

struct gezira_Window_ {
    gezira_Image_t image;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    void *pixels = malloc (width * height * sizeof (uint32_t));
    gezira_Image_init (&window->image, pixels, width, height, width);
}

static char
gezira_Window_key_pressed (gezira_Window_t *window)
    { return -1; }

static void
gezira_Window_fini (gezira_Window_t *window)
    { free (window->image.pixels); }

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
    { return out; }

#elif defined(__APPLE__)

#include <ApplicationServices/ApplicationServices.h>
#include <objc/objc-runtime.h>
#define NSTitledWindowMask                           1
#define NSBackingStoreBuffered                       2
#define NSAnyEventMask                       ULONG_MAX
#define NSKeyDown                                   10
#define NSApplicationActivationPolicyRegular         0
typedef long NSEventType;
extern void* const NSDefaultRunLoopMode;

struct gezira_Window_ {
    gezira_Image_t image;
    id             pool;
    id             NSApp;
    id             nswindow;
    CGContextRef   context;
    CGContextRef   bitmap;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    id nscontext;
    CGColorSpaceRef colorspace;
    void *pixels = malloc (width * height * sizeof (uint32_t));
    gezira_Image_init (&window->image, pixels, width, height, width);

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
        CGRectMake (0, 0, width, height),
        NSTitledWindowMask, NSBackingStoreBuffered, NO);
    objc_msgSend (window->nswindow, sel_getUid ("makeKeyAndOrderFront:"), window->NSApp);

    /* CGContexts */
    nscontext = objc_msgSend (objc_getClass ("NSGraphicsContext"), sel_getUid ("currentContext"));
    window->context = (CGContextRef) objc_msgSend (nscontext, sel_getUid ("graphicsPort"));
    colorspace = CGColorSpaceCreateDeviceRGB ();
    window->bitmap = CGBitmapContextCreate (pixels, width, height, 8, width * 4, colorspace,
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
    free (window->image.pixels);
}

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Window_t *window = *((gezira_Window_t **) nile_Process_vars (p));
    CGImageRef image = CGBitmapContextCreateImage (window->bitmap);
    CGContextDrawImage (window->context, CGRectMake (0, 0, window->image.width, window->image.height), image);
    CGImageRelease (image);
    CGContextFlush (window->context);
    return out;
}

#elif defined (_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct gezira_Window_ {
    gezira_Image_t image;
    BITMAPINFO     bmi;
    HWND           win32window;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    BITMAPINFO bmi = { {
        sizeof (BITMAPINFOHEADER),
        width,
        -height,
        1,
        32,
        BI_RGB,
        0, 0, 0, 0, 0
    } };
    void *pixels = malloc (width * height * sizeof (uint32_t));
    gezira_Image_init (&window->image, pixels, width, height, width);
    window->win32window = CreateWindow ("STATIC", NULL, WS_VISIBLE, // WS_BORDER WS_POPUP WS_CAPTION WS_OVERLAPPED
                                        0, 0, width, height,
                                        NULL, NULL, NULL, 0);
    window->bmi = bmi;
}

static char
gezira_Window_key_pressed (gezira_Window_t *window)
    { return -1; }

static void
gezira_Window_fini (gezira_Window_t *window)
{
    DestroyWindow (window->win32window);
    free (window->image.pixels);
}

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Window_t *window = *((gezira_Window_t **) nile_Process_vars (p));
    HDC dc = GetDC (window->win32window);
    SetDIBitsToDevice (dc, 0, 0, window->image.width, window->image.height, 0, 0,
                       0, window->image.height, window->image.pixels, &window->bmi, DIB_RGB_COLORS);
    ReleaseDC (window->win32window, dc);
    return out;
}

#elif defined (__unix__)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct gezira_Window_ {
    gezira_Image_t   image;
    XShmSegmentInfo *segment;
    Display         *display;
    GC               gc;
    XImage          *ximage;
    Window           x11window;
};

static void
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    int depth;
    Atom atom;
    window->segment = (XShmSegmentInfo *) malloc (sizeof (XShmSegmentInfo));
    window->display = XOpenDisplay (0);
    window->gc = DefaultGC (window->display, DefaultScreen (window->display));
    depth = XDefaultDepth (window->display, DefaultScreen (window->display));
    if (!(depth == 24 || depth == 32)) {
        fprintf (stderr, "Unsupported display depth: %d\n", depth);
        exit (1);
    }
    window->ximage = XShmCreateImage (window->display, CopyFromParent, depth, ZPixmap,
                                     NULL, window->segment, width, height);
    window->x11window = XCreateWindow (window->display, DefaultRootWindow (window->display),
                                       50, 50, width, height, 0, depth, InputOutput,
                                       CopyFromParent, 0, NULL);
    window->segment->shmid = shmget (IPC_PRIVATE, window->ximage->bytes_per_line * height,
                                     IPC_CREAT | 0777);
    window->segment->shmaddr = window->ximage->data =
        (char *) shmat (window->segment->shmid, 0, 0);
    gezira_Image_init (&window->image, window->ximage->data, width, height, width);
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
    XDestroyImage (window->ximage);
    shmdt (window->segment->shmaddr);
    free (window->segment);
    XDestroyWindow (window->display, window->x11window);
    XCloseDisplay (window->display);
}

static nile_Buffer_t *
gezira_WindowUpdate_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Window_t *window = *((gezira_Window_t **) nile_Process_vars (p));
    XShmPutImage (window->display, window->x11window, window->gc, window->ximage, 0, 0, 0, 0,
                  window->ximage->width, window->ximage->height, False);
    XSync (window->display, False);
    return out;
}

#else
#error Unsupported platform!
#endif

static nile_Process_t *
gezira_WindowUpdate (nile_Process_t *p, gezira_Window_t *window)
{
    nile_Process_t *parent = p;
    p = nile_Process (p, 1, sizeof (gezira_WindowUpdate_vars_t),
                      gezira_WindowUpdate_prologue, NULL, NULL);
    if (p) {
        gezira_WindowUpdate_vars_t *vars = nile_Process_vars (p);
        nile_Process_t *nextGate = nile_Identity (parent, 1);
        vars->window = window;
        nile_Process_gate (p, nextGate);
        if (window->image.gate)
            p = nile_Process_pipe (window->image.gate, p, NILE_NULL);
        window->image.gate = nextGate;
    }
    return p;
}

static void
gezira_Window_update_and_clear (gezira_Window_t *window, nile_Process_t *init,
                                float a, float r, float g, float b)
{
    nile_Process_feed (gezira_WindowUpdate (init, window), NULL, 0);
    nile_Process_feed (nile_Process_pipe (
            gezira_RectangleSpans (init, 0, 0, window->image.width, window->image.height),
            gezira_CompositeUniformColorOverImage_ARGB32 (init, &window->image, a, r, g, b),
            NILE_NULL),
        NULL, 0);
}

#endif
