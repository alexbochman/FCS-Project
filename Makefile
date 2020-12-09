
CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic

all: main.o Alphabet.o DFA.hpp NFA.hpp Regex.hpp
	$(CC) -std=c++17 main.o Alphabet.o DFA.hpp NFA.hpp Regex.hpp -o main $(LIBS)

main.o: main.cpp NFA.hpp Regex.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++17

Alphabet.o: Alphabet.cpp Alphabet.hpp
	$(CC) $(CFLAGS) -o $@ $< -std=c++17

clean:
	rm main *.o