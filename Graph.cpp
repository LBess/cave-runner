#include "Graph.h"

//// Graph ////
Graph::Graph()
: mat(std::vector<int>()), height(0), width(0)
{}

Graph::Graph(std::vector<Tile*>& tiles, Point dimensions)
: height(dimensions.y), width(dimensions.x)
{
    char tileVal;
    int matTileCtr = 0; // Counting up how many tiles (Empty, Start, and End) there are in the adjacency matrix
    for (int i = 0; i < tiles.size(); ++i) {
        // Giving each tile a row index in the adjacency matrix
        tileVal = tiles[i]->val;
        if (tileVal == EMPTY_TILE || tileVal == START_TILE || tileVal == END_TILE) {
            tiles[i]->matIndex = matTileCtr;
            ++matTileCtr;
        }
    }
    mat = std::vector<int>(matTileCtr * matTileCtr, 0);

    int top, bottom, left, right;
    for (int i = 0; i < tiles.size(); ++i) {
        // This can be made more efficient by constructing an adjacency matrix of 0's and then running the algorithm
        // Such that whenever a 0 is changed to a 1, the connected node is changed to a 1 as well
        tileVal = tiles[i]->val;
        if (tileVal == EMPTY_TILE || tileVal == START_TILE || tileVal == END_TILE) {
            // Testing whether or not the adjacent tiles to tiles[i] are Empty tiles
            // First edge-cases are checked (Top, Bottom, Left, Right, and Corners)
            // Else the tile has four adjacent tiles
            // The indexes of the adjacent tiles are stored in the indexes vector, to be refrenced when checking whether they themselves are Empty tiles or not
            std::vector<int> adjTileIndexes(4, -1); // Top, Bottom, Left, Right
            // Edge-cases first
            if (i < width) {
                // Top
                adjTileIndexes[1] = i + width;
                if (i % width == 0) {
                    // Left Side
                    adjTileIndexes[3] = i + 1;
                } else if (i % width == width - 1) {
                    // Right Side
                    adjTileIndexes[2] = i - 1;
                } else {
                    adjTileIndexes[3] = i + 1;
                }
            } else if (i > width * height - width) {
                // Bottom
                adjTileIndexes[0] = i - width;
                if (i % width == 0) {
                    // Left Side
                    adjTileIndexes[3] = i + 1;
                } else if (i % width == width - 1) {
                    // Right Side
                    adjTileIndexes[2] = i - 1;
                } else {
                    adjTileIndexes[3] = i + 1;
                    adjTileIndexes[2] = i - 1;
                }
            } else if (i % width == 0) {
                // Left
                adjTileIndexes[3] = i + 1;
                if (i < width) {
                    // Top Side
                    adjTileIndexes[1] = i + width;
                } else if (i > width * height - width) {
                    // Bottom Side
                    adjTileIndexes[0] = i - width;
                } else {
                    adjTileIndexes[1] = i + width;
                    adjTileIndexes[0] = i - width;
                }
            } else if (i % width == width - 1) {
                // Right
                adjTileIndexes[2] = i - 1;
                if (i < width) {
                    // Top Side
                    adjTileIndexes[1] = i + width;
                } else if (i > width * height - width) {
                    // Bottom Side
                    adjTileIndexes[0] = i - width;
                } else {
                    adjTileIndexes[1] = i + width;
                    adjTileIndexes[0] = i - width;
                }
            } else {
                adjTileIndexes[0] = i - width;
                adjTileIndexes[1] = i + width;
                adjTileIndexes[2] = i - 1;
                adjTileIndexes[3] = i + 1;
            }

            int currentTileIndex, matchedTileIndex;
            Tile* matchedTile;
            for (int j = 0; j < adjTileIndexes.size(); ++j) {
                matchedTile = tiles[adjTileIndexes[j]];
                if (matchedTile->val == EMPTY_TILE || matchedTile->val == START_TILE || matchedTile->val == END_TILE) {
                    // 2D -> 1D Mapping
                    // Since it's an adjacency matrix, height == width
                    currentTileIndex = tiles[i]->matIndex;
                    matchedTileIndex = matchedTile->matIndex;
                    if (mat[currentTileIndex + matchedTileIndex * matTileCtr] == 0) {
                        // Checking if they've already been connected or not
                        // If not, connect them, such that for BFS we don't need to recheck each edge
                        mat[currentTileIndex + matchedTileIndex * matTileCtr] = 1;
                        mat[matchedTileIndex + currentTileIndex * matTileCtr] = 1;
                        tiles[i]->edges.push_back(matchedTile); // Connecting the nodes
                        matchedTile->edges.push_back(tiles[i]);
                    }
                }
            }
            nodes.push_back(tiles[i]);
        }
        // else do nothing, b/c the adjacency matrix is already initialized to 0
    }
    boardTiles = &tiles;
}

int Graph::BFS(Player player, Goblin goblin)
{
    std::queue<Tile*> nodeQueue;

    int playerNodeIndex, goblinNodeIndex;
    for (int i = 0; i < nodes.size(); ++ i) {
        // Initializng nodes' visited and parent parameters
        nodes[i]->parent = nullptr;
        if (nodes[i]->boardIndex == goblin.boardIndex) {
            // The BFS starts at the goblin node, so it's marked as visited
            nodes[i]->visited = true;   // (Don't get your ='s and =='s mixed up haha)
            nodeQueue.push(nodes[i]);
            goblinNodeIndex = i;
        } else {
            nodes[i]->visited = false;
        }

        if (nodes[i]->boardIndex == player.boardIndex) {
            playerNodeIndex = i;
        }
    }

    Tile* currentNode;
    Tile* connectedNode;
    while (!nodeQueue.empty()) {
        // The queue is necessary for BFS, it'll continue on until either all of the recursively connected nodes to the source node
        // have been checked, or until it reaches the target node
        currentNode = nodeQueue.front();
        nodeQueue.pop();
        if (currentNode->boardIndex == nodes[playerNodeIndex]->boardIndex) {
            break;  // Player reached
        }
        for (int i = 0; i < currentNode->edges.size(); ++i) {
            connectedNode = currentNode->edges[i];
            if (!connectedNode->visited) {
                connectedNode->visited = true;  // Marking as visited so it can't be revisited
                connectedNode->parent = currentNode;
                nodeQueue.push(connectedNode);
            }
        }
    }

    Tile* node = nodes[playerNodeIndex];
    int goblinMoveIndex;
    while (node->parent != nodes[goblinNodeIndex] && node->parent != nullptr) {
        // Tracing back from the Player (last node in the BFS) to the Goblin (Source Node) via the parent parameter. 
        // This generates the shortest path between the two.
        // Second predicate necessary for when the Goblin occupies the same tile as the player
        node = node->parent;
    }
    goblinMoveIndex = node->boardIndex; // Returning the FIRST move the Goblin makes on its path
    return goblinMoveIndex;
}

void Graph::print()
{
    char intChar;
    std::ofstream file("adjMatrix.txt");
    for (int i = 0; i < mat.size(); ++i) {
        intChar = '0' + mat[i];
        file << intChar;
        if (i % (nodes.size()) == nodes.size() - 1) {
            file << '\n';
        } else {
            file << ' ';
        }
    }
    file.close();
}
////////