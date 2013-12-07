#include "PlanetRed.hpp"
#include "SDL.hpp"

PlanetRed::PlanetRed(Sprite* sprite, float hitpoints, float x, float y, int w, int h)
    : Planet(sprite, hitpoints, x, y, w, h)
{
}
void PlanetRed::update(uint32_t dt)
{
    UNUSED(dt);

    // Will check if the user clicked inside me. If so, will attack
    // myself with random damage

    // InputManager* input = InputManager::getInstance();

    // No more damage
    // if ((input->isMouseInside(this->box->x, this->box->y, this->box->w, this->box->h)) &&
    //     (input->isMouseDown(SDL_BUTTON_LEFT)))
    //     this->damage(SDL::randomNumberBetween(1, 20));
}

