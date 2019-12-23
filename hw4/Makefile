all: scrabble

scrabble: scrabble.cpp Bag.o Board.o ConsolePrinter.o Dictionary.o Player.o Move.o
	g++ -g -Wall -w -std=c++11 $^ -o $@

Bag.o: Bag.cpp Bag.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@

Board.o: Board.cpp Board.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@

Dictionary.o: Dictionary.cpp Dictionary.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@

Player.o: Player.cpp Player.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@

ConsolePrinter.o: ConsolePrinter.cpp ConsolePrinter.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@

Move.o: Move.cpp Move.h
	g++ -g -Wall -w -std=c++11 -c $< -o $@



