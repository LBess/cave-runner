#include <iostream>

#include "Board.h"

//// Functions ////
WINDOW* create_win(int width, int height)
{
    // Center of terminal
    int start_x = (COLS - width) / 2;
    int start_y = (LINES - height) / 2;

    WINDOW* local_win = newwin(height, width*2, start_y, start_x); // Multiply width by 2 to account for spaces
    wrefresh(local_win);

    return local_win;
}
///////////////

//// Board ////
Board::Board()
: dimensions(Point())
{}

Board::Board(int x, int y)
: dimensions(Point(x, y)), board(new std::vector<Tile>), player(Player(Point(x/2, y/2))), goblins(std::vector<Goblin>()), win(create_win(x, y)) 
{
    for (int i = 0; i < x*y; ++i) {
        // Generating the empty board
        if (i < dimensions.x || i % dimensions.x == 0 || i % dimensions.x == dimensions.x - 1 || i > x*(y-1)) { 
            // First Row || First Column || Last Column || Last Row
            board->push_back(Tile(WALL_TILE));
        } else {
            board->push_back(Tile(EMPTY_TILE));
        }
    }
    tileGraph = Graph(board, dimensions);
    //tileGraph.print();
}

Board::Board(std::string filePath)
: board(new std::vector<Tile>), goblins(std::vector<Goblin>())
{
    std::ifstream file(filePath);
    if (file.is_open()) {
        int x, y, i, a, b;
        file >> x >> y; // First two entries in maze file
        dimensions = Point(x, y);
        win = (create_win(x, y));

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
                    player = Player(Point(x, y));
                    board->push_back(Tile(c));
                } else if (c == GOBLIN_TILE) {
                    x = i % dimensions.x;
                    y = (i - x) / dimensions.x;
                    Point goblinPosition = Point(x, y);
                    goblins.push_back(Goblin(goblinPosition));
                    board->push_back(Tile(EMPTY_TILE));
                } else {
                    board->push_back(Tile(c));
                }
                ++i; // Only incrementing on non-newline chars
            }
        }
        file.close();
    } else {
        throw std::runtime_error ("Can't open file: " + filePath + '\n');
    }
    tileGraph = Graph(board, dimensions);
    tileGraph.print();
}

void Board::input(int in)
{
    int i;
    Point newPosition = player.position;
    try {
        switch (in) {
            case 'W':
                newPosition.y = player.position.y - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'w':
                newPosition.y = player.position.y - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'A':
                newPosition.x = player.position.x - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'a':
                newPosition.x = player.position.x - 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'S':
                newPosition.y = player.position.y + 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 's':
                newPosition.y = player.position.y + 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'D':
                newPosition.x = player.position.x + 1;
                i = newPosition.x + dimensions.x * newPosition.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'd':
                newPosition.x = player.position.x + 1;
                i = newPosition.x + dimensions.x * player.position.y;
                if ((*board)[i].val == WALL_TILE) {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            default:
                break;
        }
    } catch (std::out_of_range ex) {
        //printw(ex.what());
    }
}

void Board::goblinMove()
{
    // for (int i = 0; i != goblins.size(); ++i) {
    //     // Call Djikstra's (tileGraph.search()) from this code block
    //     goblins[i].position = Point(goblins[i].position.x, goblins[i].position.y - 1);
    // }
}

void Board::print()
{
    delwin(win);
    win = create_win(dimensions.x, dimensions.y);

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
    for (int i = 0; i < board->size(); ++i) {
        goblinCheck = false;
        ti = (*board)[i].val;
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
            if (ti == END_TILE) {
                victory = true;
            }
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