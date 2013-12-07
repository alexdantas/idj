#ifndef EARTH_H_DEFINED
#define EARTH_H_DEFINED

#include "Planet.hpp"

class Earth: public Planet
{
public:
    Earth(Sprite* sprite, float hp, float x, float y, int w, int h);

    void update(uint32_t dt);

private:
    float speedX;
    float speedY;
    float walkingSpeed;
};

#endif /* EARTH_H_DEFINED */
