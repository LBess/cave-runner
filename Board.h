#ifndef BOARD
#define BOARD

#include <stdexcept>

#include "Graph.h"

class Board
{
private:
    Point dimensions;
    Point endTile;
    std::vector<Tile*> board;
    Graph tileGraph;

    Player player;
    std::vector<Goblin> goblins;
    
    WINDOW* win;
    bool goblinHit = false;

public:
    Board();
    Board(int x, int y);
    Board(std::string filePath);
    bool input(int in);
    void goblinMove();
    void print();
    bool checkVictory() { return (player.position == endTile) ? (true) : (false); }
    bool getGoblinHit() { return goblinHit; }
};

#endif