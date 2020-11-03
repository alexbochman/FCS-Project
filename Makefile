
CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic

all: main.o Alphabet.o DFA.hpp NFA.hpp
	$(CC) main.o Alphabet.o DFA.hpp NFA.hpp -o main $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++17

Alphabet.o: Alphabet.cpp Alphabet.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++17

clean:
	rm main *.o