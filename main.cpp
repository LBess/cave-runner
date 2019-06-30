#include "Board.h"

int main(void)
{
    // ncurses initialization
    initscr();
    cbreak();   // Line buffering disabled
    noecho();
    keypad(stdscr, true);   // F1

    int usrInput;
    Board board = Board(9, 9);
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
    }

    erase();
    printw("Exiting");
    refresh();

    // ncurses deinitialization
    getch();
    endwin();
    return 0;
}


