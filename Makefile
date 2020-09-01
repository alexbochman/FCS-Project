
CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic


all: main.o TEMP.o
	$(CC) main.o TEMP.o -o main $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

TEMP.o: TEMP.cpp TEMP.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

clean:
	rm main *.o