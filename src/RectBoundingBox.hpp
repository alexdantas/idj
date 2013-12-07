#ifndef RECTBOUNDINGBOX_H_DEFINED
#define RECTBOUNDINGBOX_H_DEFINED

// TODO TODO BUG BUT WARNING WARNING
//
// I cant seem to make this hierarchy work
//
// RectBoundingBox and CircBoundingBox are specializations of
// this class.
//
// But when I try to do the overlaps() method between them, it fucks
// up...
//
// Maybe an explanation?

#include <iostream> // for NULL
#include "Shapes.hpp"

/// Defines a rectangular bounding box to detect collisions
//  between things.
//
//
class RectBoundingBox
{
public:
    /// Creates the bounding box with specified size.
    RectBoundingBox(float x, float y, int w, int h);

    /// Creates the bounding box based on an existing rectangle.
    RectBoundingBox(Rectangle* rect);

    ~RectBoundingBox();

    /// Tells if we've collided with #other rectangular thing.
    bool overlaps(RectBoundingBox* other);

    /// Tells if we've collided with #other circular thing.
//    bool overlaps(CircBoundingBox* other);

    /// Shows bounding box onscreen for debugging purposes.
    void render(float cameraX, float cameraY);

private:

    /// The x/y/w/h of the bounding box.
    Rectangle* rect;

    /// Tells us if we're using a rectangle from another class.
    //  That's important so we don't delete it from memory when this
    //  class is destroyed.
    bool externalRect;
};

#endif /* RECTBOUNDINGBOX_H_DEFINED */
