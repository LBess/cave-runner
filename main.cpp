#include "Board.h"

Board load_maze(std::string filePath)
{
    Board board;
    
    try {
        board = Board(filePath);
    } catch (std::runtime_error ex) {
        printw(ex.what());
    }

    return board;
}

int main(void)
{
    // ncurses initialization
    initscr();
    cbreak();   // Line buffering disabled
    noecho();
    keypad(stdscr, true);   // F1

    int usrInput;
    //Board board = Board(9, 9);
    Board board = Board("mazes/1");
    board.print();

    printw("Press Q to exit\n");
    printw("Enter WASD to move\n");
    refresh();

    while (usrInput = getch()) {
        erase();
        printw("Press Q to exit\n");
        printw("Enter WASD to move\n");
        refresh();
        if (usrInput == 'Q' || usrInput == 'q') {
            break;
        }
        board.input(usrInput);
        board.print();
        if (board.getVictory()) {
            printw("You won!\n");
            break;
        }
    }

    printw("Enter a key to exit...");
    refresh();

    // ncurses deinitialization
    getch();
    endwin();
    return 0;
}


