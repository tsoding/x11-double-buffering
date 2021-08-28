# X11 Double Buffering Experiment

Trying different approaches to Double Buffering in Pure X11 applications on Linux:

- [No Double Buffering](./db_none.c)
- [Xdbe](./db_xdbe.c)
- [Back Buffer in Pixmap](./db_pixmap.c)
- [Back Buffer in XImage](./db_ximage.c)

## Quick Start

```console
$ make
$ ./main.none
$ ./main.xdbe
$ ./main.pixmap
$ ./main.ximage
```
