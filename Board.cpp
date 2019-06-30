#include "Board.h"

Board::Board(int x, int y)
: size_x(x), size_y(y), board(new std::vector<Tile>) 
{
    // for (int i = 0; i < x; ++i) {
    //     for (int j = 0; j < y; ++j) {
    //         if (i == 0 || i == x - 1 || j == 0) {
    //             board->push_back(Tile('W'));
    //         } else {
    //             board->push_back(Tile(' '));  
    //         }        
    //     }   
    // }
    for (int i = 0; i < x*y; ++i) {
        // Generating the empty board
        if (i < size_x || i % size_x == 0 || i % size_x == size_x - 1 || i > x*(y-1)) { 
            // First Row || First Column || Last Column || Last Row
            board->push_back(Tile('W'));
        } else {
            board->push_back(Tile(' '));
        }
    }
}

void Board::print()
{
    for (int i = 0; i < board->size(); ++i) {
        std::cout << (*board)[i].val;
        if (i % size_x == size_x - 1) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        } 
    }
}
