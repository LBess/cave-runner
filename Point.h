#ifndef POINT
#define POINT

struct Point
{
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
    int x;
    int y;
    bool operator== (const Point& RHS)
    {
        if (this->x == RHS.x and this->y == RHS.y) {
            return true;
        } else {
            return false;
        }
    }
};

#endif