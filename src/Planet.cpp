#include "Planet.hpp"
#include "GameStateGame.hpp"

Planet::Planet(Sprite* sprite, float hp, float x, float y, int w, int h):
    GameObject(x, y, w, h),
    DamageableObject(hp),
    sprite(NULL)
{
    this->sprite = sprite;
}
void Planet::render(float cameraX, float cameraY)
{
    if (!this->sprite) return;

    if (GameStateGame::showBoundingBoxes)
        this->boundingBox->render(cameraX, cameraY);

    this->sprite->render((int)(this->box->x - cameraX),
                         (int)(this->box->y - cameraY));
}

