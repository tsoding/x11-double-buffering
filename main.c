#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 120
#define RECT_WIDTH 300
#define RECT_HEIGHT 300

int main(void)
{
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

    XWindowAttributes wa = {0};
    XGetWindowAttributes(display, window, &wa);

    GC gc = XCreateGC(display, window, 0, NULL);

    Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    XSelectInput(display, window, KeyPressMask);

    XMapWindow(display, window);

    XSetForeground(display, gc, 0xFF0000);

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

        XClearArea(display, window, 0, 0, WIDTH, HEIGHT, False);
        XFillRectangle(display, window, gc, rect_x, rect_y, RECT_WIDTH, RECT_HEIGHT);

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
