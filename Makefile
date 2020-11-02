#variables
C=g++
CFLAGS=-c -std=c++17

all : dgame

dgame : dgame.o
	$(C) dgame.o -o dgame

dgame.o : dgame.cpp src/inchar.h src/sinput.h
	$(C) $(CFLAGS) dgame.cpp

clean :
	rm dgame.o

destroy :
	rm -r src
	rm dgame.o dgame.cpp Makefile README dgame
