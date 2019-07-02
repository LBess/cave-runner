#ifndef BOARD
#define BOARD

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ncurses.h>

#include "Character.h"

// Tile Macros
#define EMPTY_TILE ' '
#define WALL_TILE 'W'
#define START_TILE 'S'
#define END_TILE 'E'
#define PLAYER_TILE 'P'
#define GOBLIN_TILE 'G'

struct Tile
{
    Tile();
    Tile(char c);
    char val;    
};

class Board
{
public:
    Board();
    Board(int x, int y);
    Board(std::string filePath);
    void input(int in);
    void print();
    bool getVictory() { return victory; }

private:
    Point dimensions;
    std::vector<Tile>* board;
    
    Player player;
    std::vector<Goblin>* goblins;
    
    WINDOW* win;
    bool victory = false;
};

#endif