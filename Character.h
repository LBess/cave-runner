#ifndef CHARACTER
#define CHARACTER

#include "Point.h"

class Character
{
public:
    Character(Point p = Point());
    Point position;
};

class Player : public Character 
{
public:
    Player(Point p = Point(), int h = 10);
    int health;
};

class Goblin : public Character
{
public:
    Goblin(Point p = Point(), int s = 1, int a = 2);
    int speed;
    int attack;
};

#endif