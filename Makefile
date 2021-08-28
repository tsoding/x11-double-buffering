CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=-lX11 -lXext

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
