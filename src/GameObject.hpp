#ifndef GAMEOBJECT_H_DEFINED
#define GAMEOBJECT_H_DEFINED

#include <stdint.h> // uint32_t
#include "Shapes.hpp"
#include "RectBoundingBox.hpp"

class GameObject
{
public:
    GameObject(float x=0.0, float y=0.0, int w=0, int h=0);
    ~GameObject();

    /// Updates all the object's internal states.
    virtual void update(uint32_t dt) = 0;

    /// Shows object onscreen.
    virtual void render(float cameraX, float cameraY) = 0;

    /// Tells if we've collided with another thing.
    bool collidedWith(GameObject* other);

    float getX();
    float getY();
    int   getWidth();
    int   getHeight();

protected:

    /// Object's size and position.
    Rectangle* box;

    /// Collision check box.
    RectBoundingBox* boundingBox;
};

#endif /* GAMEOBJECT_H_DEFINED */
