#define DB_IMPL_NAME "Xdbe"

typedef struct {
    Display *display;
    Window window;
    GC gc;
    XdbeBackBuffer back_buffer;
} DB;

void db_init(DB *db, Display *display, Window window)
{
    int major_version_return, minor_version_return;
    if(XdbeQueryExtension(display, &major_version_return, &minor_version_return)) {
        printf("XDBE version %d.%d\n", major_version_return, minor_version_return);
    } else {
        fprintf(stderr, "XDBE is not supported!!!1\n");
        exit(1);
    }

    db->display = display;
    db->window = window;
    db->gc = XCreateGC(display, window, 0, NULL);
    db->back_buffer = XdbeAllocateBackBufferName(display, window, 0);
}

void db_clear(DB *db)
{
    XSetForeground(db->display, db->gc, 0);
    XFillRectangle(db->display, db->back_buffer, db->gc, 0, 0, WIDTH, HEIGHT);
}

void db_fill_rect(DB *db, int x, int y, int w, int h)
{
    XSetForeground(db->display, db->gc, 0xFF0000);
    XFillRectangle(db->display, db->back_buffer, db->gc, x, y, w, h);
}

void db_swap_buffers(DB *db)
{
    XdbeSwapInfo swap_info;
    swap_info.swap_window = db->window;
    swap_info.swap_action = 0;
    XdbeSwapBuffers(db->display, &swap_info, 1);
}
