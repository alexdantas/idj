/// @file Shapes.hpp
//
//  This file defines a set of basic shapes that can be used
//  for... pretty much whatever

#ifndef SHAPES_H_DEFINED
#define SHAPES_H_DEFINED

struct Point
{
    float x;
    float y;

    Point(float x, float y);
};

struct Rectangle
{
    float x; ///< X of the top left point
    float y; ///< Y of the top left point
    int   w; ///< Width
    int   h; ///< Height

    float centerX; ///< X of the center point
    float centerY; ///< Y of the center point

    float dx; ///< This is always x + w
    float dy; ///< This is always y + h

    /// Creates a sweet rectangle with *x* and *y* coordinates and
    /// *w* and *y* dimensions.
    Rectangle(float x, float y, int w, int h);

    /// Adds to the current x.
    /// Although this seems useless, you must call this instead of
    /// modifying x directly because it refreshes internal points.
    void addX(float x);

    /// Adds to the current y.
    /// Although this seems useless, you must call this instead of
    /// modifying y directly because it refreshes internal points.
    void addY(float y);
};

struct Circle
{
    float x;
    float y;
    int   r;

    float centerX;
    float centerY;

    /// Creates a nice circle with *x* and *y* coordinates and *r*
    /// radius.
    Circle(float x, float y, int r);

    /// Adds to the current x.
    /// Although this seems useless, you must call this instead of
    /// modifying x directly because it refreshes internal points.
    void addX(float x);

    /// Adds to the current y.
    /// Although this seems useless, you must call this instead of
    /// modifying y directly because it refreshes internal points.
    void addY(float y);
};

#endif /* SHAPES_H_DEFINED */

