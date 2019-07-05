#include <menu.h>
#include "Board.h"
#include <stdlib.h>
#include <stdio.h>

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

std::string startScreen()
{
    int c;
    char maze1 [] = "Maze 1";
    char maze2 [] = "Maze 2";
    char maze3 [] = "Maze 3";
    char quit [] = "Quit";
    char* menuChoice;
    std::vector<char*> choices = {maze1, maze2, maze3, quit};
    ITEM** startItems;
    startItems = (ITEM **)calloc(choices.size() + 1, sizeof(ITEM *));   // Oh no...
    for (int i = 0; i < choices.size(); ++i) {
        startItems[i] = new_item(choices[i], choices[i]);
    }
    startItems[choices.size()] = NULL;

    MENU* startMenu;
    startMenu = new_menu((ITEM**)startItems);
    WINDOW* startMenuWin;
    startMenuWin = newwin(5, 9, (LINES - 5) / 2, (COLS - 9) / 2);
    keypad(startMenuWin, TRUE);
    set_menu_win(startMenu, startMenuWin);  // Connecting menu and window
    set_menu_mark(startMenu, " * ");

    post_menu(startMenu);
    wrefresh(startMenuWin);

    int row = 0;
    std::string chosenItemName;
    bool end = false;
    while ((c = getch()) != KEY_F(1)) {
        switch(c) {
            case KEY_UP:
                // Move menu selection up
                menu_driver(startMenu, REQ_UP_ITEM);
                if (row > 0) {
                    --row;
                }
                break;
            case KEY_DOWN:
                // Move menu selection down
                menu_driver(startMenu, REQ_DOWN_ITEM);
                if (row < 4) {
                    ++row;
                }
                break;
            case 10:
                // Terminating Action
                end = true;
                chosenItemName = choices[row];
                break;
        }
        if (end) {
            break;
        }
        wrefresh(startMenuWin);
    }
    
    // Unpost menu and free up memory
    unpost_menu(startMenu);
    free_menu(startMenu);
    for (int i = 0; i < choices.size(); ++i) {
        free_item(startItems[i]);
    }

    delwin(startMenuWin);
    return chosenItemName;
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
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    curs_set(0);    // Hiding cursor

    bool replay = true;

    while (replay) {
        std::string startChoice;
        int usrInput, moveNumber;
        char moveNumberChar;
        Board board;

        printw("Use arrow keys to navigate the menu and ENTER to select an option\n");
        startChoice = startScreen();

        if (startChoice != "Quit") {
            
            if (startChoice == "Maze 1") {
                board = Board("mazes/1");
            } else if (startChoice == "Maze 2") {
                board = Board("mazes/2");
            } else {
                board = Board("mazes/3");
            }

            moveNumber = 1;
            char buffer [10];
            sprintf(buffer, "%d", moveNumber);
            printw("Move number: ");
            printw(buffer);
            addch('\n');
            printw("Enter WASD key to start and move\n");
            refresh();
            board.print();
            
            bool invalidInput;
            bool checkInput;
            while (usrInput = getch()) {
                invalidInput = false;
                char buffer [10];   // Don't overflow please

                if (usrInput == KEY_UP || usrInput == 'w') {
                    usrInput = 'W';
                } else if (usrInput == KEY_DOWN || usrInput == 's') {
                    usrInput = 'S';
                } else if (usrInput == KEY_LEFT || usrInput == 'a') {
                    usrInput = 'A';
                } else if (usrInput == KEY_RIGHT || usrInput == 'd') {
                    usrInput = 'D';
                } else {
                    invalidInput = true;
                }

                if (!invalidInput) {
                    checkInput = board.input(usrInput);
                        if (checkInput) {
                        // If the move is valid (Isn't going into a wall)
                        board.goblinMove();
                        if (board.getGoblinHit()) {
                            printw("You've been eaten by the goblin!\n");
                            break;
                        } else if (board.checkVictory()) {
                            printw("You won!\n");         
                            break;
                        }
                        ++moveNumber;
                    }
                }
                
                erase();
                sprintf(buffer, "%d", moveNumber);
                printw("Move number: ");
                printw(buffer);
                addch('\n');
                refresh();
                board.print();
            }

            printw("Enter a F1 to return to menu or F2 to exit\n");
            refresh();
            board.print();
            int c;
            
            if ((c = getch()) != KEY_F(1)) {
                replay = false;
            } else {
                replay = true;
                erase();
            }
        } else {
            replay = false;
        }
    }
    // ncurses deinitialization
    endwin();
    return 0;
}