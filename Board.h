#ifndef BOARD
#define BOARD

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Graph.h"

class Board
{
private:
    Point dimensions;
    std::vector<Tile>* board;
    Graph tileGraph;

    Player player;
    std::vector<Goblin> goblins;
    
    WINDOW* win;
    bool victory = false;

public:
    Board();
    Board(int x, int y);
    Board(std::string filePath);
    void input(int in);
    void goblinMove();
    void print();
    bool getVictory() { return victory; }

};

#endif