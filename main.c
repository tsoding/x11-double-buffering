#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xdbe.h>

#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 120
#define RECT_WIDTH 300
#define RECT_HEIGHT 300

#define DB_NONE   0
#define DB_XDBE   1
#define DB_PIXMAP 2
#define DB_XIMAGE 3

#if DB_IMPL == DB_NONE
#  include "./db_none.c"
#elif DB_IMPL == DB_XDBE
#  include "./db_xdbe.c"
#elif DB_IMPL == DB_PIXMAP
#  include "./db_pixmap.c"
#elif DB_IMPL == DB_XIMAGE
#  include "./db_ximage.c"
#else
#  error "Unsupported Double Buffering approach"
#endif

int main(void)
{
    printf("Double Buffering Implementation: "DB_IMPL_NAME"\n");

    DB db = {0};

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "ERROR: could not open the default display\n");
        exit(1);
    }

    Window window = XCreateSimpleWindow(
                        display,
                        XDefaultRootWindow(display),
                        0, 0,
                        WIDTH, HEIGHT,
                        0,
                        0,
                        0);

    db_init(&db, display, window);

    XWindowAttributes wa = {0};
    XGetWindowAttributes(display, window, &wa);

    Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    XSelectInput(display, window, KeyPressMask);

    XMapWindow(display, window);

    int rect_x = 10;
    int rect_y = 10;

    int rect_dx = -1;
    int rect_dy = -1;

    int quit = 0;
    while (!quit) {
        while (XPending(display) > 0) {
            XEvent event = {0};
            XNextEvent(display, &event);
            switch (event.type) {
            case KeyPress: {
                switch (XLookupKeysym(&event.xkey, 0)) {
                case 'q':
                    quit = 1;
                    break;
                default:
                {}
                }
            } break;
            case ClientMessage: {
                if ((Atom) event.xclient.data.l[0] == wm_delete_window) {
                    quit = 1;
                }
            }
            break;
            }
        }

        db_clear(&db);
        db_fill_rect(&db, rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT);
        db_swap_buffers(&db);

        int rect_nx = rect_x + rect_dx;
        if (rect_nx <= 0 || rect_nx + RECT_WIDTH >= WIDTH) {
            rect_dx *= -1;
        } else {
            rect_x = rect_nx;
        }

        int rect_ny = rect_y + rect_dy;
        if (rect_ny <= 0 || rect_ny + RECT_HEIGHT >= HEIGHT) {
            rect_dy *= -1;
        } else {
            rect_y = rect_ny;
        }

        usleep(1000*1000/FPS);
    }

    XCloseDisplay(display);
    return 0;
}
