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
    keypad(stdscr, TRUE);   // Function Key and Numpad usability
    start_color();   // Allows for use of colors
    init_pair(1, COLOR_BLUE, COLOR_BLACK);  // Pairing colors (Foreground, Background)
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    curs_set(0);    // Hiding cursor

    int usrInput;
    Board board = Board("mazes/1");
    board.print();

    printw("Press Q to exit\n");
    printw("Enter WASD to move\n");
    refresh();

    while (usrInput = getch()) {
        erase();
        board.print();
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


