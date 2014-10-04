CC = g++
CFLAGS = -Wall -std=c++11 -g

all:	webCrawler

webCrawler.o:	webCrawler.cpp
	$(CC) -c $< -o $@ $(CFLAGS) 

webCrawler:	webCrawler.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ webCrawler pairing