CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lX11 -lXext

.PHONY: all
all: main.none main.xdbe main.pixmap 

main.none: main.c
	$(CC) $(CFLAGS) -DDB_IMPL=DB_NONE -o main.none main.c $(LIBS)

main.xdbe: main.c
	$(CC) $(CFLAGS) -DDB_IMPL=DB_XDBE -o main.xdbe main.c $(LIBS)

main.pixmap: main.c
	$(CC) $(CFLAGS) -DDB_IMPL=DB_PIXMAP -o main.pixmap main.c $(LIBS)
