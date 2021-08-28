#define DB_IMPL_NAME "None"

typedef struct {
    Display *display;
    Window window;
    GC gc;
} DB;

void db_init(DB *db, Display *display, Window window)
{
    db->display = display;
    db->window = window;
    db->gc = XCreateGC(display, window, 0, NULL);
}

void db_clear(DB *db)
{
    XClearArea(db->display, db->window, 0, 0, WIDTH, HEIGHT, False);
}

void db_fill_rect(DB *db, int x, int y, int w, int h)
{
    XSetForeground(db->display, db->gc, 0xFF0000);
    XFillRectangle(db->display, db->window, db->gc, x, y, w, h);
}

#define db_swap_buffers(...)
