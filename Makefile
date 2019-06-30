CXX = g++

main: main.o board.o
    g++ -g -o main main.o board.o

main.o: main.cpp board.o
    g++ -g -c main.cpp board.o 

board.o: board.cpp board.h tile.o
    g++ -g -c board.cpp board.h tile.o

tile.o: tile.cpp tile.h
    g++ -g -c tile.cpp tile.h

