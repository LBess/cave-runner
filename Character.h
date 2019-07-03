#ifndef CHARACTER
#define CHARACTER

#include "Point.h"

class Character
{
public:
    Point position;
    Character(Point p = Point()) : position(Point(p)) {}
};

class Player : public Character 
{
public:
    int health;
    Player(Point p = Point(), int h = 10) : Character(p), health(h) {}
};

class Goblin : public Character
{
public:
    int speed;
    int attack;
    Goblin(Point p, int s = 1, int a = 2) : Character(p), speed(s), attack(a) {}
};

#endif