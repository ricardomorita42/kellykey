CFLAGS=-Wall -ansi -pedantic
CC=gcc
ALLEGRO=-lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf 
#=================================

main: main.o rio.o grade.o debugger.o config.o graficos.o 
	$(CC) $(CFLAGS) main.o rio.o grade.o debugger.o config.o graficos.o -o main -lm $(ALLEGRO)

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

graficos.o: graficos.c graficos.h
	$(CC) $(CFLAGS) -c graficos.c 

clean:
	-rm *.o
