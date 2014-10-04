CC = g++
CFLAGS = -Wall -std=c++11 -g

OBJ_DIR = bin

all:	grading qsort heap_test

$(OBJ_DIR)/qsort.o:	qsort.cpp qsort.h
	$(CC) -c $< -o $@ $(CFLAGS) 

$(OBJ_DIR)/grading.o:	grading.cpp msort.h
	$(CC) -c $< -o $@ $(CFLAGS) 

$(OBJ_DIR)/heap_test.o:	heap_test.cpp heapImpl.h heap.h
	$(CC) -c $< -o $@ $(CFLAGS) 

qsort:	$(OBJ_DIR)/qsort.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

grading:	$(OBJ_DIR)/grading.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

heap_test:	$(OBJ_DIR)/heap_test.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ grading heap_test qsort
