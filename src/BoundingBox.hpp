#ifndef BOUNDINGBOX_H_DEFINED
#define BOUNDINGBOX_H_DEFINED

// Pre-defining the classes.
// (without this, we get into a circular #include hell)
class CircBoundingBox;
class RectBoundingBox;

/// A dummy interface for general bounding boxes.
//
//  This should not be instantiated, this should only be used as a
//  general pointer for specific collision algorithms.
//
//  Like this:
//  <pre>
//  BoundingBox* box1 = new RectBoundingBox(...);
//  BoundingBox* box2 = new CircBoundingBox(...);
//
//  if (box1->overlaps(box2))
//  ...
//  </pre>
class BoundingBox
{
public:
    virtual ~BoundingBox();

    /// All subclasses must implement collision detection with circles.
    virtual bool overlaps(CircBoundingBox* other) = 0;

    /// All subclasses must implement collision detection with rectangles.
    virtual bool overlaps(RectBoundingBox* other) = 0;

    /// All subclasses must implement rendering for debugging purposes.
    virtual void render(float cameraX, float cameraY) = 0;

private:
};

#endif /* BOUNDINGBOX_H_DEFINED */
