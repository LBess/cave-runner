#include <vector>
#include <iostream>
#include <stdexcept>
#include <ncurses.h>
#include "Tile.h"

struct Point
{
    Point(int a, int b);
    int x;
    int y;
};

class Board
{
public:
    Board(int x, int y);
    void input(int in);
    void print();

private:
    Point size;
    Point player;
    std::vector<Tile>* board;
    WINDOW* win;
};