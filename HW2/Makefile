CC = g++
CFLAGS = -Wall -std=c++11 -g

OBJ = hw2q4.o hw2q5.o

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

all: hw2q4 hw2q5

hw2q4:	hw2q4.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
hw2q5:	hw2q5.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f *.o *~ hw2q4 hw2q5
