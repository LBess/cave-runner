#include <iostream>

#include "Board.h"

//// Utility Functions ////
WINDOW* createWin(int width, int height)
{
    // Center of terminal
    int start_x = (COLS - width) / 2;
    int start_y = (LINES - height) / 2;

    WINDOW* local_win = newwin(height, width*2, start_y, start_x); // Multiply width by 2 to account for spaces
    wrefresh(local_win);

    return local_win;
}
////////

//// Board ////
Board::Board()
: dimensions(Point())
{}

Board::Board(int x, int y)
: dimensions(Point(x, y)), board(std::vector<Tile*>()), win(createWin(x, y)) 
{
    for (int i = 0; i < x*y; ++i) {
        // Generating the empty board
        if (i < dimensions.x || i % dimensions.x == 0 || i % dimensions.x == dimensions.x - 1 || i > x*(y-1)) { 
            // First Row || First Column || Last Column || Last Row
            board.push_back(new Tile(WALL_TILE, i));
        } else {
            board.push_back(new Tile(EMPTY_TILE, i));
        }
    }
    tileGraph = Graph(board, dimensions);
}

Board::Board(std::string filePath)
: board(std::vector<Tile*>()), goblins(std::vector<Goblin>())
{
    std::ifstream file(filePath);
    if (file.is_open()) {
        int x, y, i, a, b;
        file >> x >> y; // First two entries in maze file
        dimensions = Point(x, y);
        win = (createWin(x, y));

        char c;
        i = 0;
        while (file.get(c)) {
            if (c != '\n') {
                if (c == START_TILE) {
                    // Player starting position
                    // Reverse mapping, 1D -> 2D
                    // i = x + width * y
                    // x = i % width
                    // y = (i - x) / width => Derived from the 2D -> 1D equation
                    x = i % dimensions.x;
                    y = (i - x) / dimensions.x;
                    player = Player(Point(x, y), i);
                    board.push_back(new Tile(c, i));
                } else if (c == GOBLIN_TILE) {
                    x = i % dimensions.x;
                    y = (i - x) / dimensions.x;
                    Point goblinPosition = Point(x, y);
                    goblins.push_back(Goblin(goblinPosition, i));
                    board.push_back(new Tile(EMPTY_TILE, i));
                } else if (c == END_TILE) {
                    x = i % dimensions.x;
                    y = (i - x) / dimensions.x;
                    endTile = Point(x, y);  
                    board.push_back(new Tile(c, i));
                } else {
                    board.push_back(new Tile(c, i));
                }
                ++i; // Only incrementing on non-newline chars
            }
        }
        file.close();
    } else {
        throw std::runtime_error ("Can't open file: " + filePath + '\n');
    }
    tileGraph = Graph(board, dimensions);
}

void Board::deallocate()
{
    for (int i = 0; i < board.size(); ++i) {
        delete board[i];
    }
}

bool Board::input(int in)
{
    int i;
    Point newPosition = player.position;
    try {
        switch (in) {
            case 'W':
                newPosition.y = player.position.y - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if (board[i]->val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = Player(newPosition, i);
                }
                break;

            case 'A':
                newPosition.x = player.position.x - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if (board[i]->val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = Player(newPosition, i);
                }
                break;

            case 'S':
                newPosition.y = player.position.y + 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if (board[i]->val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = Player(newPosition, i);
                }
                break;

            case 'D':
                newPosition.x = player.position.x + 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if (board[i]->val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = Player(newPosition, i);
                }
                break;

            default:
                break;
        }
    } catch (std::out_of_range ex) {
        //printw(ex.what());
        return false;   // Invalid move
    }
    return true;
}

void Board::goblinMove()
{
    int moveIndex, moveX, moveY;
    for (int i = 0; i != goblins.size(); ++i) {
        moveIndex = tileGraph.BFS(player, goblins[i]);
        goblins[i].boardIndex = moveIndex;
        moveX = moveIndex % dimensions.x;
        moveY = (moveIndex - moveX) / dimensions.x;
        goblins[i].position = Point(moveX, moveY);
        if (goblins[i].position == player.position) {
            goblinHit = true;
        }
    }
}

void Board::print()
{
    delwin(win);
    win = createWin(dimensions.x, dimensions.y);

    std::vector<int> goblin_indexes;
    Point goblin_point;
    int in;
    for (auto it = goblins.begin(); it != goblins.end(); ++it) {
        goblin_point = it->position;
        in = goblin_point.x + dimensions.x * goblin_point.y;
        goblin_indexes.push_back(in);
    }

    char ti;
    bool goblinCheck;
    for (int i = 0; i < board.size(); ++i) {
        goblinCheck = false;
        ti = board[i]->val;
        for (auto it = goblin_indexes.begin(); it != goblin_indexes.end(); ++it) {
            if (i == *it) {
                goblinCheck = true;
                break;
            }
        }
        if (goblinCheck) {
            waddch(win, GOBLIN_TILE | COLOR_PAIR(2));
        } else if (i == player.position.x + dimensions.x * player.position.y) {
            // 2D -> 1D Mapping Formula: i = x + width * y
            waddch(win, PLAYER_TILE | COLOR_PAIR(1));
        } else {
            if (ti == START_TILE) {
                waddch(win, ti | COLOR_PAIR(3));
            } else if (ti == END_TILE) {
                waddch(win, ti | COLOR_PAIR(3));
            } else {
                waddch(win, ti);
            }
        }
        if (i % dimensions.x == dimensions.x - 1) {
            waddch(win, '\n');
        } else {
            waddch(win, EMPTY_TILE);
        } 
    }
    wrefresh(win);
}
////////////