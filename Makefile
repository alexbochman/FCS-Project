
CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic


all: main.o Character.o Alphabet.o Str.o
	$(CC) main.o Character.o Alphabet.o Str.o -o main $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

Character.o: Character.cpp Character.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

Alphabet.o: Alphabet.cpp Alphabet.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

Str.o: Str.cpp Str.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++14

clean:
	rm main *.o