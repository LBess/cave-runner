#ifndef GRAPH
#define GRAPH

#include <ncurses.h>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include "Tile.h"
#include "Character.h"

// An undirected graph represented with an adjacency matrix
// Consider the empty tile do be the parent tile of the goblin, player, start, and end tiles
// Each node in the graph is an empty tile

// struct Node
// {
//     char val;
//     int index;  // Index in the adjacency matrix
//     Node (char v, int i) : val(v), index(i) {}
// };

class Graph
{
// Adjacency Matrix, a 2D-Array of size N^2
// matrix[i][j] == 1 only if Node_i and Node_j are empty tiles and are adjacent (up, down, left right) to one another
// If i==j, then matrix[i][j] == 0
private:
    std::vector<int> mat;
    std::vector<Tile*> nodes;    // Empty tiles
    std::vector<Tile*>* boardTiles;
    int height; // Board Height
    int width;  // Board Width

public:
    Graph();
    Graph(std::vector<Tile*>& tiles, Point dimensions);
    int BFS(Player player, Goblin goblin);
    void print();
};

#endif