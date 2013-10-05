SOURCES:=gtkapp.c
CC:=gcc
CFLAGS:=`pkg-config --libs --cflags gtk+-2.0`

all:
	$(CC)  -o bin/amy amyplay.c $(CFLAGS)
