CC = g++
CFLAGS = -Wall -std=c++11 -g

all:	boolean arraylist_test speed_test

boolean.o:	boolean.cpp stack.h stackImpl.h arraylist.h arraylistImpl.h ilist.h Map/Map.h Map/MapImpl.h
	$(CC) -c $< -o $@ $(CFLAGS) 
	
arraylist_test.o:	arraylist_test.cpp arraylist.h arraylistImpl.h ilist.h
	$(CC) -c $< -o $@ $(CFLAGS) 

speed_test.o:	speed_test.cpp arraylist.h arraylistImpl.h ilist.h
	$(CC) -c $< -o $@ $(CFLAGS) 

boolean:	boolean.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

arraylist_test:	arraylist_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

speed_test:	speed_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f *.o *~ boolean arraylist_test speed_test
