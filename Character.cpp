#include "Character.h"

Character::Character(Point p)
: position(Point(p))
{}

Player::Player(Point p, int h)
: Character(p), health(h)
{}

Goblin::Goblin(Point p, int s, int a)
: Character(p), speed(s), attack(a)
{}