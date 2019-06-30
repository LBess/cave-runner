#include "Board.h"

WINDOW* create_win(int width, int height)
{
    // Center of screen
    int start_x = (COLS - width) / 2;
    int start_y = (LINES - height) / 2;

    WINDOW* local_win = newwin(height, width*2, start_y, start_x); // Multiply width by 2 to account for spaces
    //box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW* win)
{
    //wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}

Point::Point(int a, int b)
: x(a), y(b)
{}

Board::Board(int x, int y)
: size(Point(x, y)), player(Point(x/2, y/2)), board(new std::vector<Tile>), win(create_win(x, y)) 
{
    for (int i = 0; i < x*y; ++i) {
        // Generating the empty board
        if (i < size.x || i % size.x == 0 || i % size.x == size.x - 1 || i > x*(y-1)) { 
            // First Row || First Column || Last Column || Last Row
            board->push_back(Tile('W'));
        } else {
            board->push_back(Tile(' '));
        }
    }
}

void Board::input(int in)
{
    int i;
    Point newPosition = player;
    try {
        switch (in) {
            case 'W':
                newPosition.y = player.y - 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'w':
                newPosition.y = player.y - 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'A':
                newPosition.x = player.x - 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'a':
                newPosition.x = player.x - 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'S':
                newPosition.y = player.y + 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 's':
                newPosition.y = player.y + 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            case 'D':
                newPosition.x = player.x + 1;
                i = newPosition.x + size.x * newPosition.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;
            case 'd':
                newPosition.x = player.x + 1;
                i = newPosition.x + size.x * player.y;
                if ((*board)[i].val == 'W') {
                    throw std::out_of_range ("Can't walk into walls silly!\n");
                } else {
                    player = newPosition;
                }
                break;

            default:
                break;
        }
    } catch (std::out_of_range ex) {
        printw(ex.what());
    }
}

void Board::print()
{
    //destroy_win(win);
    delwin(win);
    win = create_win(size.x, size.y);

    for (int i = 0; i < board->size(); ++i) {
        char msg = (*board)[i].val;

        if (i == player.x + size.x * player.y) {
            // 2D -> 1D Mapping Formula: i = x + width * y
            waddch(win, 'P');
        } else {
            waddch(win, msg);
        }
        if (i % size.x == size.x - 1) {
            waddch(win, '\n');
        } else {
            waddch(win, ' ');
        } 
    }

    wrefresh(win);
}
