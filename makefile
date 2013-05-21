CFLAGS=-Wall -ansi -pedantic
CC=gcc
#=================================

main: main.o rio.o grade.o debugger.o config.o
	$(CC) $(CFLAGS) main.o rio.o grade.o debugger.o config.o -o main -lm && rm *.o

main.o: main.c rio.h
	$(CC) $(CFLAGS) -c main.c

rio.o: rio.c rio.h grade.h
	$(CC) $(CFLAGS) -c rio.c

grade.o: grade.c grade.h rio.h
	$(CC) $(CFLAGS) -c grade.c

debugger.o: debugger.c debugger.h
	$(CC) $(CFLAGS) -c debugger.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c
