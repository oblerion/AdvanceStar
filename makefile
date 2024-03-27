#! /bin/bash
all:
	./make
# CC=gcc
# CFLAGS=-g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# INC=
# EXEC=main
# DOBJ=build/linux64/
#
# all: main.o Map.o SpriteSheet.o MapEditor.o Game.o Icons.o
# 	$(CC) $(DOBJ)main.o $(DOBJ)Map.o $(DOBJ)SpriteSheet.o $(DOBJ)MapEditor.o $(DOBJ)Game.o $(DOBJ)Icons.o $(CFLAGS) -o $(EXEC)
#
# main.o: src/main.c
# 	$(CC) -c src/main.c $(INC) -g -Wall -o $(DOBJ)main.o
#
# Map.o: src/Map.c
# 	$(CC) -c src/Map.c $(INC) -g -Wall -o $(DOBJ)Map.o
#
# SpriteSheet.o: src/SpriteSheet.c
# 	$(CC) -c src/SpriteSheet.c $(INC) -g -Wall -o $(DOBJ)SpriteSheet.o
#
# MapEditor.o: src/MapEditor.c
# 	$(CC) -c src/MapEditor.c $(INC) -g -Wall -o $(DOBJ)MapEditor.o
#
# Game.o: src/Game.c
# 	$(CC) -c src/Game.c $(INC) -g -Wall -o $(DOBJ)Game.o
#
# Icons.o: src/Icons.c
# 	$(CC) -c src/Icons.c $(INC) -g -Wall -o $(DOBJ)Icons.o
#
#
# clean:
# 	rm -f $(DOBJ)*.o
