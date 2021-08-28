#define DB_IMPL_NAME "XImage"

typedef struct {
    Display *display;
    Window window;
    GC gc;
    uint32_t *pixels;
    XImage *image;
} DB;

void db_init(DB *db, Display *display, Window window)
{
    db->display = display;
    db->window = window;
    db->gc = XCreateGC(display, window, 0, NULL);
    db->pixels = malloc(sizeof(uint32_t) * WIDTH * HEIGHT);

    XWindowAttributes wa = {0};
    XGetWindowAttributes(display, window, &wa);

    db->image = XCreateImage(display,
                             wa.visual,
                             wa.depth,
                             ZPixmap,
                             0,
                             (char*) db->pixels,
                             WIDTH, HEIGHT,
                             32,
                             WIDTH * sizeof(uint32_t));
}

void db_clear(DB *db)
{
    memset(db->pixels, 0, sizeof(uint32_t) * WIDTH * HEIGHT);
}

void db_fill_rect(DB *db, int x0, int y0, unsigned int w, unsigned int h)
{
    for (unsigned int dx = 0; dx < w; ++dx) {
        for (unsigned int dy = 0; dy < h; ++dy) {
            int x = x0 + dx;
            int y = y0 + dy;

            if (0 <= x && (unsigned int) x < WIDTH &&
                    0 <= y && (unsigned int) y < HEIGHT) {
                db->pixels[y*WIDTH + x] = 0xFF0000;
            }
        }
    }
}

void db_swap_buffers(DB *db)
{
    XPutImage(db->display, db->window, db->gc, db->image, 0, 0, 0, 0, WIDTH, HEIGHT);
}
