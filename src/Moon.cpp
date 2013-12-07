#include "Moon.hpp"
#include <math.h>

Moon::Moon(Sprite* sprite, float hp, Planet* center, int w, int h)
    : Planet(sprite, hp, center->getX(), center->getY(), w, h)
{
    this->center = NULL;
    this->center = center;

    this->radius = (center->getWidth())/2;
    this->angle  = 0;

    this->rotatingSpeed = 0.003;
}
void Moon::update(uint32_t dt)
{
    this->angle += this->rotatingSpeed * dt;

    // x and y offsets of where the Moon should orbit around.
    int xOffset = this->center->getX() + this->radius - this->box->w/2;
    int yOffset = this->center->getY() + this->radius - this->box->h/2;

    this->box->x = xOffset + (cos(this->angle) * this->radius);
    this->box->y = yOffset + (sin(this->angle) * this->radius);
}

