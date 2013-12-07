#ifndef GRAPHICS_H_DEFINED
#define GRAPHICS_H_DEFINED

#include "SDL/SDL.h"
#include "Color.hpp"
#include "Shapes.hpp"

class Graphics
{
public:
    /// Initializes graphics mode on SDL screen #screen.
    //
    //  @note If this is not called at all, there will be no
    //        drawings available!
    static void init(SDL_Surface* Screen);

    /// Draws a line from [xy]1 to [xy]2 with #spacing.
    static void drawSpacedLine(Point a, Point b, Color color=Color(255, 0, 255), int spacing=5);

    /// Draws a line with thickness #width.
    static void drawThickLine(Point a, Point b, Color color, int width);

    /// Draws a rectangle based on sizes #x, #y, #w and #h.
    static void drawRectangle(int x, int y, int w, int h, Color color=Color(255, 0, 255));

    /// Draws a rectangle based on the rectangle #rect.
    static void drawRectangle(Rectangle  rect, Color color=Color(255, 0, 255));

    /// Draws a rectangle based on the rectangle pointer #rect.
    static void drawRectangle(Rectangle* rect, Color color=Color(255, 0, 255));

    // /// Draws a circle onscreen.
    // static void drawRectangle(int x, int y, int r, Color color);
    // static void drawCircle(Circle  circ  Color color=Color(255, 0, 255));
    // static void drawCircle(Circle* circ, Color color=Color(255, 0, 255));

private:

    /// The SDL's internal screen data structure.
    static SDL_Surface* screen;
};

#endif /* GRAPHICS_H_DEFINED */
