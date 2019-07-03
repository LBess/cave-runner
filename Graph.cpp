#include "Graph.h"

Graph::Graph()
: mat(std::vector<int>()), matCopy(std::vector<int>()), nodes(std::vector<Node*>()), height(0), width(0)
{}

Graph::Graph(std::vector<Tile>* tiles, Point dimensions)
: mat(std::vector<int>(tiles->size()*tiles->size(), 0)), matCopy(std::vector<int>()), nodes(std::vector<Node*>()), height(dimensions.y), width(dimensions.x)
{
    for (int i = 0; i < tiles->size(); ++i) {
        // Giving each tile a row index in the adjacency matrix
        (*tiles)[i].mat_index = i;
    }

    char tileVal;
    int top, bottom, left, right;
    for (int i = 0; i < tiles->size(); ++i) {
        // This can be made more efficient by constructing an adjacency matrix of 0's and then running the algorithm
        // Such that whenever a 0 is changed to a 1, the connected node is changed to a 1 as well
        tileVal = (*tiles)[i].val;
        if (tileVal == EMPTY_TILE || tileVal == START_TILE || tileVal == END_TILE) {
            // Testing whether or not the adjacent tiles to tiles[i] are Empty tiles
            // First edge-cases are checked (Top, Bottom, Left, Right, and Corners)
            // Else the tile has four adjacent tiles
            // The indexes of the adjacent tiles are stored in the indexes vector, to be refrenced when checking whether they themselves are Empty tiles or not
            std::vector<int> indexes;
            top = -1;
            bottom = -1;
            left = -1;
            right = -1;
            // Edge-cases first
            if (i < width) {
                // Top
                bottom = i + width;
                if (i % width == 0) {
                    // Left Side
                    right = i + 1;
                } else if (i % width == width - 1) {
                    // Right Side
                    left = i - 1;
                } else {
                    right = i + 1;
                    left = i - 1;
                }
            } else if (i > width * height - width) {
                // Bottom
                top = i - width;
                if (i % width == 0) {
                    // Left Side
                    right = i + 1;
                } else if (i % width == width - 1) {
                    // Right Side
                    left = i - 1;
                } else {
                    right = i - 1;
                    left = i + 1;
                }
            } else if (i % width == 0) {
                // Left
                right = i + 1;
                if (i < width) {
                    // Top Side
                    bottom = i + width;
                } else if (i > width * height - width) {
                    // Bottom Side
                    top = i - width;
                } else {
                    bottom = i + width;
                    top = i - width;
                }
            } else if (i % width == width - 1) {
                // Right
                left = i + 1;
                if (i < width) {
                    // Top Side
                    bottom = i + width;
                } else if (i > width * height - width) {
                    // Bottom Side
                    top = i - width;
                } else {
                    bottom = i + width;
                    top = i - width;
                }
            } else {
                top = i - width;
                bottom = i + width;
                left = i + 1;
                right = i - 1;
            }

            if (top != -1) {
                indexes.push_back(top);
            }
            if (bottom != -1) {
                indexes.push_back(bottom);
            }
            if (left != -1) {
                indexes.push_back(left);
            }
            if (right != -1) {
                indexes.push_back(right);
            }

            int currentTileIndex, matchedTileIndex;
            Tile matchedTile;
            for (int j = 0; j < indexes.size(); ++j) {
                matchedTile = (*tiles)[indexes[j]];
                if (matchedTile.val == EMPTY_TILE || matchedTile.val == START_TILE || matchedTile.val == END_TILE) {
                    // 2D -> 1D Mapping
                    // Since it's an adjacency matrix, height == width
                    currentTileIndex = (*tiles)[i].mat_index;
                    matchedTileIndex = matchedTile.mat_index;
                    mat[currentTileIndex + matchedTileIndex * tiles->size()] = 1;
                    mat[matchedTileIndex + currentTileIndex * tiles->size()] = 1;
                    //break;
                }
            }
        }
        // else do nothing, b/c the adjacency matrix is already initialized to 0
    }
}

void Graph::djikstras(Point player, Point goblin)
{

}


void Graph::print()
{
    char intChar;
    std::ofstream file("adjMatrix.txt");
    for (int i = 0; i < mat.size(); ++i) {
        intChar = '0' + mat[i];
        file << intChar;
        if (i % (width*width) == width*width - 1) {
            file << '\n';
        } else {
            file << ' ';
        }
    }
    file.close();
}