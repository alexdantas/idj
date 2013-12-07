#include "Shapes.hpp"

Point::Point(float x, float y):
    x(x),
    y(y)
{
}

Rectangle::Rectangle(float x, float y, int w, int h):
    x(x),
    y(y),
    w(w),
    h(h)
{
    this->centerX = x + (w/2);
    this->centerY = y + (h/2);

    this->dx = x + w;
    this->dy = y + h;
}
void Rectangle::addX(float x)
{
    this->x       += x;
    this->dx      += x;
    this->centerX += x;
}
void Rectangle::addY(float y)
{
    this->y       += y;
    this->dy      += y;
    this->centerY += y;
}

Circle::Circle(float x, float y, int r):
    x(x),
    y(y),
    r(r)
{
    this->centerX = x + r;
    this->centerY = y + r;
}
void Circle::addX(float x)
{
    this->x       += x;
    this->centerX += x;
}
void Circle::addY(float y)
{
    this->y       += y;
    this->centerY += y;
}

