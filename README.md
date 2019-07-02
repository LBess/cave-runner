# Cave Runner

## Description: A C++ maze game

## To compile: Requires ncurses, must link with ncurses library, see Makefile for g++ example.

## Designs Goals:
### First pass (C)
#### i. Basic game loop (C)
##### > Loop progressing whenver player makes a valid move (C)
#### ii. User input (C)
##### > Take from keyboard (C)
##### > Reject if going into wall (C)
#### iii. Maze tiles (C)
##### > Empty spaces (C)
##### > Start (C)
##### > Finish (C)
##### > Walls (C)
#### iv. Load mazes from text files (C)
### Second pass (*)
#### i. Randomly generated mazes (*)
##### > Different options for maze size and complexity (*)
##### > Python script to generate maze (*)
#### ii. Leaderboard ()
##### > Maze specific
##### > User inputs name
#### iii. AI Goblin chasing player ()
##### > Goblin only moves when player moves ()
#### iv. New tiles ()
##### > Open new passages ()
##### > Slow down Goblin ()
#### v. Error checking on custom mazes ()
#### vi. Beautify game (*)
##### > Colors (*)
##### > Borders around window ()
##### > Different Wall tiles based on location (Vertical, Horizontal, Corner, etc.)
### Third pass ()
#### i. Multi stage levels
##### > Procedurally generate each time ()
##### > Staircase Tile ()