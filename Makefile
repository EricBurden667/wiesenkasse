CC=g++
CFLAGS=-c -Wall
LDLIBS=-lsqlite3

all: Wiesenkasse

Wiesenkasse: api.o
	$(CC) -o Wiesenkasse api.o

api.o: api.cpp
	$(CC) $(CFLAGS) $(LDLIBS) api.cpp

clean:
	rm -rf *o Wiesenkasse
