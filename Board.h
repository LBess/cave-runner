#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <ncurses.h>
#include "Tile.h"

struct Point
{
    Point();
    Point(int a, int b);
    int x;
    int y;
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
    Point size;
    Point player;
    std::vector<Tile>* board;
    WINDOW* win;
    bool victory = false;
};