#ifndef PLANETRED_H_DEFINED
#define PLANETRED_H_DEFINED

#include "Planet.hpp"

class PlanetRed: public Planet
{
public:
    PlanetRed(Sprite* sprite, float hitpoints, float x, float y, int w, int h);

    /// Updates PlanetRed based on input from InputManager.
    void update(uint32_t dt);

private:
};

#endif /* PLANETRED_H_DEFINED */
