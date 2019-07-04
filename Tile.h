#ifndef TILE
#define TILE

#include <vector>

// Tile Macros
#define EMPTY_TILE ' '
#define WALL_TILE 'W'
#define START_TILE 'S'
#define END_TILE 'E'
#define PLAYER_TILE 'P'
#define GOBLIN_TILE 'G'

struct Tile
{
    // Tile doubles up as a Node for Graph

    char val;
    int boardIndex;

    // Graph vars
    int matIndex = 0;  // Adjacency matrix row index
    Tile* parent = nullptr;
    std::vector<Tile*> edges;
    bool visited = false;

    Tile(): val(EMPTY_TILE) , boardIndex(0) {}
    Tile(char c, int i): val(c), boardIndex(i) {}
};

#endif