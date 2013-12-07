#include "CircBoundingBox.hpp"
#include "Graphics.hpp"
#include <cmath>

CircBoundingBox::CircBoundingBox(float x, float y, int r)
{
    this->circ = NULL;
    this->circ = new Circle(x, y, r);

    this->externalCirc = false;
}
CircBoundingBox::CircBoundingBox(Circle* circ)
{
    this->circ = NULL;
    this->circ = circ;

    this->externalCirc = true;
}
CircBoundingBox::~CircBoundingBox()
{
    if (!(this->externalCirc))
        if (this->circ)
            delete this->circ;
}
bool CircBoundingBox::overlaps(CircBoundingBox* other)
{
    if (!other)      return false;
    if (!this->circ) return false;

    // We'll see if the distance between them is less than the sum of
    // the two radii.
    // If it is, they're overlapping each other!

    Circle* A = this->circ;
    Circle* B = other->circ;

    float diffX = A->centerX - B->centerX;
    float diffY = A->centerY - B->centerY;

    // Get distance with Pythagoras
    float distance = sqrt((diffX * diffX) + (diffY * diffY));

    return (distance <= (A->r + B->r));
}
// bool CircBoundingBox::overlaps(RectBoundingBox* other)
// {
//     // TODO
//     return false;
// }


void CircBoundingBox::render(float cameraX, float cameraY)
{
    if (!this->circ) return;

    Circle tmp(this->circ->x - cameraX,
               this->circ->y - cameraY,
               this->circ->r);

    // Random blinking colors up this thing!
    Color color;
    color.randomize();

//    Graphics::drawCircle(tmp, color);
}

