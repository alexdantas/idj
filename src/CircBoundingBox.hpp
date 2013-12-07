#ifndef CIRCBOUNDINGBOX_H_DEFINED
#define CIRCBOUNDINGBOX_H_DEFINED

#include <iostream> // for NULL
#include "Shapes.hpp"

/// Defines a circular bounding box to detect collisions
//  between things.
//
class CircBoundingBox
{
public:
    /// Creates the bounding box with specified size.
    CircBoundingBox(float x, float y, int r);

    /// Creates the bounding box based on an existing circle.
    CircBoundingBox(Circle* circ);

    ~CircBoundingBox();

    /// Tells if we've collided with #other circular thing.
    bool overlaps(CircBoundingBox* other);

    /// Tells if we've collided with #other rectangular thing.
    /// TODO
//    bool overlaps(RectBoundingBox* other);

    /// Shows bounding box onscreen for debugging purposes.
    void render(float cameraX, float cameraY);

private:

    /// The x/y/r of the bounding box.
    Circle* circ;

    /// Tells us if we're using a circle from another class.
    //  That's important so we don't delete it from memory when this
    //  class is destroyed.
    bool externalCirc;
};

#endif /* CIRCBOUNDINGBOX_H_DEFINED */
