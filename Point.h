#ifndef POINT
#define POINT

struct Point
{
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
    int x;
    int y;
};

#endif