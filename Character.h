#ifndef CHARACTER
#define CHARACTER

#include "Point.h"

class Character
{
public:
    Point position;
    int boardIndex;
    Character(Point p, int i) : position(Point(p)), boardIndex(i) {}
};

class Player : public Character 
{
public:
    bool alive = true;
    Player() : Character(Point(), 0) {}
    Player(Point p, int i) : Character(p, i) {}
};

class Goblin : public Character
{
public:
    int speed;
    Goblin(Point p, int i, int s = 1) : Character(p, i), speed(s) {}
};

#endif