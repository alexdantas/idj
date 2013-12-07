#include "Earth.hpp"
#include "Log.hpp"

Earth::Earth(Sprite* sprite, float hp, float x, float y, int w, int h):
    Planet(sprite, hp, x, y, w, h),
    speedX(0),
    speedY(0),
    walkingSpeed(0.3)
{
    Log::debug("Earth::Earth Created at (" +
               SDL::intToString(x) + ", " +
               SDL::intToString(y) + ")");
}
void Earth::update(uint32_t dt)
{
    UNUSED(dt);
}

