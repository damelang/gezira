#ifndef GEZIRA_WINDOW_H
#define GEZIRA_WINDOW_H

typedef struct gezira_Window_ gezira_Window_t;

typedef struct {
    gezira_Window_t *window;
} gezira_WindowUpdate_vars_t;

#ifdef __APPLE__

#include <ApplicationServices/ApplicationServices.h>
#include <objc/objc-runtime.h>
#define NSTitledWindowMask     1
#define NSBackingStoreBuffered 2

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
gezira_Window_init (gezira_Window_t *window, int width, int height)
{
    id nscontext;
    CGColorSpaceRef colorspace;
    window->width = width;
    window->height = height;
    window->pixels = malloc (width * height * sizeof (uint32_t));
    window->NSApp = objc_msgSend (objc_getClass ("NSApplication"), sel_getUid ("sharedApplication"));
    window->pool = objc_msgSend (objc_getClass ("NSAutoreleasePool"), sel_getUid ("alloc"));
    objc_msgSend (window->pool, sel_getUid ("init"));
    window->nswindow = objc_msgSend (objc_getClass ("NSWindow"), sel_getUid ("alloc"));
    objc_msgSend (window->nswindow, sel_getUid ("initWithContentRect:styleMask:backing:defer:"),
        CGRectMake (0, 0, width, height),
        NSTitledWindowMask, NSBackingStoreBuffered, NO);
    objc_msgSend (window->nswindow, sel_getUid ("makeKeyAndOrderFront:"), window->NSApp);
    nscontext = objc_msgSend (objc_getClass ("NSGraphicsContext"), sel_getUid ("currentContext"));
    window->context = (CGContextRef) objc_msgSend (nscontext, sel_getUid ("graphicsPort"));
    colorspace = CGColorSpaceCreateDeviceRGB ();
    window->bitmap = CGBitmapContextCreate (window->pixels, width, height, 8, width * 4, colorspace,
                                            kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host);
    CGColorSpaceRelease (colorspace);
    CGContextSetBlendMode (window->context, kCGBlendModeCopy);
    CGContextSetRenderingIntent (window->context, kCGRenderingIntentAbsoluteColorimetric);
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

#error TODO move code over here

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

#endif
