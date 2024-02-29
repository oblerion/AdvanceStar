#! /bin/sh

CC=g++
CFLAGS=-g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
INC=
EXEC=main
DOBJ=build/linux64/


all: main.o Map.o SpriteSheet.o
	$(CC) $(DOBJ)main.o $(DOBJ)Map.o $(DOBJ)SpriteSheet.o $(CFLAGS) -o $(EXEC)
	./$(EXEC)

main.o: src/main.cpp
	$(CC) -c src/main.cpp $(INC) -g -Wall -o $(DOBJ)main.o

Map.o: src/Map.cpp
	$(CC) -c src/Map.cpp $(INC) -g -Wall -o $(DOBJ)Map.o
	
SpriteSheet.o: src/SpriteSheet.cpp
	$(CC) -c src/SpriteSheet.cpp $(INC) -g -Wall -o $(DOBJ)SpriteSheet.o

clean:
	rm -f $(DOBJ)*.o
