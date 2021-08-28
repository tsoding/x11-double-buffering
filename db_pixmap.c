#define DB_IMPL_NAME "Pixmap"

typedef struct {
    Display *display;
    Window window;
    GC gc;
    Pixmap back_buffer;
} DB;

void db_init(DB *db, Display *display, Window window)
{
    db->display = display;
    db->window = window;
    db->gc = XCreateGC(display, window, 0, NULL);
    db->back_buffer = XCreatePixmap(display, window, WIDTH, HEIGHT, 24);
}

void db_clear(DB *db)
{
    XSetForeground(db->display, db->gc, 0);
    XFillRectangle(db->display, db->back_buffer, db->gc, 0, 0, WIDTH, HEIGHT);
}

void db_fill_rect(DB *db, int x, int y, unsigned int w, unsigned int h)
{
    XSetForeground(db->display, db->gc, 0xFF0000);
    XFillRectangle(db->display, db->back_buffer, db->gc, x, y, w, h);
}

void db_swap_buffers(DB *db)
{
    XCopyArea(db->display,
              db->back_buffer,
              db->window,
              db->gc,
              0, 0,
              WIDTH, HEIGHT,
              0, 0);
}
