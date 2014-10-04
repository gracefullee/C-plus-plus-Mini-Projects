CC = g++
CFLAGS = -Wall -std=c++11 -g

OBJ = factorial.o hw3q7

HEADER_DIR=header

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

all: factorial hw3q7

hw3q7.o:	hw3q7.cpp hw3q3.h hw3q3Impl.h hw3q5.h hw3q5Impl.h
	$(CC) -c $< -o $@ $(CFLAGS) 

factorial:	factorial.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
hw3q7:	hw3q7.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f *.o *~ factorial hw3q7
