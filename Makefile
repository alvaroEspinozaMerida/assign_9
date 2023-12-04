CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++11		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: test
SRCS = graph.cpp test.cpp CityPathFinder.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

test: test.o graph.o CityPathFinder.o
	$(CC) test.o graph.o CityPathFinder.o -o test
	
clean:
	rm *.o test