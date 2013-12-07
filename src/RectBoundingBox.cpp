#include "RectBoundingBox.hpp"
#include "Graphics.hpp"

RectBoundingBox::RectBoundingBox(float x, float y, int w, int h)
{
    this->rect = NULL;
    this->rect = new Rectangle(x, y, w, h);

    this->externalRect = false;
}
RectBoundingBox::RectBoundingBox(Rectangle* rect)
{
    this->rect = NULL;
    this->rect = rect;

    this->externalRect = true;
}
RectBoundingBox::~RectBoundingBox()
{
    if (!(this->externalRect))
        if (this->rect)
            delete this->rect;
}
bool RectBoundingBox::overlaps(RectBoundingBox* other)
{
    if (!other)      return false;
    if (!this->rect) return false;

    // I tried to keep this as simple as possible.
    // But note that this method works on the negative:
    // we test if they've not collided.
    // If not, return true.

    Rectangle* A = this->rect;
    Rectangle* B = other->rect;

    // float diffX = A->x - B->x;
    // float diffY = A->y - B->y;

    // if ((diffX > B->dx) || ((-1 * diffX) > A->dx))
    //     return false;

    // if ((diffY > B->dy) || ((-1 * diffY) > A->dy))
    //     return false;

    // return true;

    // This is a very simple collision detection algorithm.
    // We have two rectangles (A and B), and we must see if they
    // DON'T intersect.
    //
    // That's summed up on this 4 rules:
    //
    // * A's bottom edge is higher than B's top edge;
    // * A's top edge is lower than B's bottom edge;
    // * A's left edge is to the right of B's right edge;
    // * A's right edge is to the left of B's left edge;

    // if (((A->dy) <= (B->y))  ||
    //     ((A->y)  >= (B->dy)) ||
    //     ((A->x)  >= (B->dx)) ||
    //     ((A->dx) <= (B->x)))
    //     return false;

    // return true;

    if ((A->x <= B->dx) &&
        (B->x <= A->dx) &&
        (A->y <= B->dy) &&
        (B->y <= A->dy))
        return true;

    return false;
}
    /// Tells if we've collided with #other circular thing.
// bool RectBoundingBox::overlaps(CircBoundingBox* other)
// {
//     // TODO
//     return false;
// }

// bool RectBoundingBox::overlaps(CircBoundingBox* other)
// {

void RectBoundingBox::render(float cameraX, float cameraY)
{
    if (!this->rect) return;

    Rectangle tmp(this->rect->x - cameraX,
                  this->rect->y - cameraY,
                  this->rect->w,
                  this->rect->h);

    // Random blinking colors up this thing!
    Color color;
    color.randomize();

    Graphics::drawRectangle(tmp, color);
}

