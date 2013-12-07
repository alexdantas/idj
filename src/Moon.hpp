#ifndef MOON_H_DEFINED
#define MOON_H_DEFINED

#include "Planet.hpp"

class Moon: public Planet
{
public:
    Moon(Sprite* sprite, float hp, Planet* center, int w, int h);

    void update(uint32_t dt);

private:
    float   radius;
    float   angle;
    Planet* center;
    float   rotatingSpeed;
};

#endif /* MOON_H_DEFINED */
