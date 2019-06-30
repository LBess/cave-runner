#include <vector>
#include <iostream>
#include "Tile.h"

class Board
{
public:
    Board(int x, int y);
    void print();

private:
    int size_x;
    int size_y;
    std::vector<Tile>* board;
};