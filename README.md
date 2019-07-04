# Cave Runner

## Description: A C++ maze game

## To compile: Requires ncurses, must link with ncurses library, see Makefile for g++ example.


## Designs Goals (C=Complete, *=In progress):
<pre>
First iteration (C)
    i. Basic game loop (C)
        > Loop progressing whenver player makes a valid move (C)
    ii. User input (C)
        > Take from keyboard (C)
        > Reject if going into wall (C)
    iii. Maze tiles (C)
        > Empty spaces (C)
        > Start (C)
        > Finish (C)
        > Walls (C)
    iv. Load mazes from text files (C)
Second iteration (*)
    i. Leaderboard ()
        > Level specific ()
        > Custom usernames ()
    ii. AI Goblin chasing player (C)
        > Adjacency matrix representation of the maze (C)
        > BFS Shortest Path Algorithm implementation for the Goblin's pathfinding (C)
    iii. More mazes ()
    iv. Beautify game (*)
        > Colors for unique tiles/characters (C)
        > Borders around window ()
        > Different Wall tiles based on location (Vertical, Horizontal, Corner, etc.) ()
    v. Improve UX ()
        > Start screen ()
            - Choose level ()
        > Game runtime ()
            - Message box with move history ()
        > End screen ()
            - Display leaderboard ()
Third iteration ()
    i. Multi stage levels ()
        > Proper game logic to handle multiple stages ()
    ii. Error checking on custom mazes ()
    iii. New tiles ()
        > Breakable Wall Tile ()
        > Stun Goblin Tile ()
        > Staircase Tile ()
Fourth iteration ()
    i. Procedurally generated mazes ()
    > Different options for maze size and complexity ()
    > Python script to generate maze ()
    > Procedurally generate mazes on the file for multi-stage levels ()
</pre>