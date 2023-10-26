CC=g++
CFLAGS=-c -Wall
LDLIBS=-lSQLiteCpp -lsqlite3
LDFLAGS=-L/usr/lib/x86_64-linux-gnu/

all: Wiesenkasse

Wiesenkasse: api.o
	$(CC) -o Wiesenkasse api.o $(LDFLAGS) $(LDLIBS)

api.o: api.cpp
	$(CC) $(CFLAGS) api.cpp

clean:
	rm -rf *.o Wiesenkasse

rebuild: clean all
