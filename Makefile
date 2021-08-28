CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lX11 -lXext

main: main.c
	$(CC) $(CFLAGS) -DDB_IMPL=0 -o main main.c $(LIBS)
