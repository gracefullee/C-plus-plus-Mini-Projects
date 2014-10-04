CC = g++
CFLAGS = -Wall -std=c++11 -g

OBJ_DIR = bin

all:	rb_test pairing

$(OBJ_DIR)/rb_test.o:	rb_test.cpp rbbst.h bst.h
	$(CC) -c $< -o $@ $(CFLAGS) 

$(OBJ_DIR)/pairing.o:	pairing.cpp
	$(CC) -c $< -o $@ $(CFLAGS) 

rb_test:	$(OBJ_DIR)/rb_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

pairing:	$(OBJ_DIR)/pairing.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY:	clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ rb_test pairing