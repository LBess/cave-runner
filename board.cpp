#include "board.h"

Board::Board(int x, int y)
: size_x(x), size_y(y), board(new std::vector<Tile>) 
{
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (i == 0 || i == x - 1 || j == 0) {
                board->push_back(Tile('W'));
            } else {
                board->push_back(Tile(' '));  
            }        
        }   
    }
}

void Board::print()
{
    std::vector<Tile> copy = *board;
    for (int i = 0; i < board->size(); ++i) {
        std::cout << copy[i].val;
        if (i % size_x == 1) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        } 
    }
}
