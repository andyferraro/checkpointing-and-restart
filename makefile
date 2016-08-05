CC=g++
#CFLAGS=-c -Wall -std=c++11
CFLAGS=-std=c++11

all: hello_iostream hello_stdio hello_cstdio heap

hello_iostream: hello_iostream.cpp
	$(CC) $(CFLAGS) hello_iostream.cpp -o hello_iostream

hello_stdio: hello_stdio.cpp
	$(CC) $(CFLAGS) hello_stdio.cpp -o hello_stdio

hello_icstdio: hello_cstdio.cpp
	$(CC) $(CFLAGS) hello_cstdio.cpp -o hello_cstdio

heap: heap.cpp
	$(CC) $(CFLAGS) heap.cpp -o heap

clean:
	rm hello_iostream hello_stdio heap
