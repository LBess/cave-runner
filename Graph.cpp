#include "Graph.h"

Graph::Graph()
: mat(std::vector<int>()), matCopy(std::vector<int>()), nodes(std::vector<Node*>()), height(0), width(0)
{}

Graph::Graph(std::vector<Tile>* tiles, Point dimensions)
: mat(std::vector<int>()), matCopy(std::vector<int>()), nodes(std::vector<Node*>()), height(dimensions.y), width(dimensions.x)
{
    char tileVal;
    int top, bottom, left, right;
    for (int i = 0; i < tiles->size(); ++i) {
        // This can be made more efficient by constructing an adjacency matrix of 0's and then running the algorithm
        // Such that whenever a 0 is changed to a 1, the connected node is changed to a 1 as well
        tileVal = (*tiles)[i].val;
        if (tileVal == EMPTY_TILE || tileVal == START_TILE || tileVal == END_TILE) {
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

            int k;
            char k_TileVal;
            for (int j = 0; j < indexes.size(); ++j) {
                k = indexes[j];
                k_TileVal = (*tiles)[k].val;
                if (k_TileVal == EMPTY_TILE || k_TileVal == START_TILE || k_TileVal == END_TILE) {
                    mat.push_back(1);
                    break;
                }
            }
        } else {
            mat.push_back(0);            
        }
    }
}

void Graph::print()
{
    char intChar;
    for (int i = 0; i < mat.size(); ++i) {
        intChar = '0' + mat[i];
        addch(intChar);
        addch(' ');
        if (i % width == width - 1) {
            addch('\n');
        }
    }
    refresh();
}