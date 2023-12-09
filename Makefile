CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++11		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: prog9
SRCS = graph.cpp CityPathFinder.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

prog9: graph.o CityPathFinder.o
	$(CC) graph.o CityPathFinder.o -o prog9

clean:
	rm *.o prog9