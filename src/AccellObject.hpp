#ifndef ACCELLOBJECT_H_DEFINED
#define ACCELLOBJECT_H_DEFINED

#include "GameObject.hpp"
#include "Animation.hpp"
#include "DamageableObject.hpp"

/// Accelerated game object.
//
//  Movements are more realistic.
class AccellObject: public GameObject,
                    public DamageableObject
{
public:

    AccellObject(Animation* anim, float x, float y, int w, int h, int hp);
    virtual ~AccellObject();

    void update(uint32_t dt);
    void render(float cameraX, float cameraY);

private:
    Animation* anim;
    bool useExternalAnimation;

    float vx; ///< Speed component of the x axis.
    float vy; ///< Speed component of the y axis.

    float ax; ///< Acceleration component of the x axis.
    float ay; ///< Acceleration component of the y axis.

    float acceleration; ///< Constant acceleration value.
    float rotation;
};

#endif /* ACCELLOBJECT_H_DEFINED */
