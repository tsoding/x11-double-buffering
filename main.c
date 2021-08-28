#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 240
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

    int rect_x = 0;
    int rect_y = 0;

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

        rect_x += 1;
        rect_y += 1;

        usleep(1000*1000/FPS);
    }

    XCloseDisplay(display);
    return 0;
}
