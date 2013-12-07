#include <cmath> // sin, cos
#include "AccellObject.hpp"
#include "InputManager.hpp"
#include "GameStateGame.hpp"

#define PI 3.1415926535

AccellObject::AccellObject(Animation* anim, float x, float y, int w, int h, int hp):
    GameObject(x, y, w, h),
    DamageableObject(hp),
    anim(anim),
    useExternalAnimation(true),
    vx(0), vy(0),
    ax(0), ay(0),
    acceleration(0.008),
    rotation(0)
{
    this->anim->start();
}
AccellObject::~AccellObject()
{
    // if (!(this->useExternalAnimation))
    //     if (this->anim) delete this->anim;
}
void AccellObject::update(uint32_t dt)
{
    this->ax = 0;
    this->ay = 0;

    InputManager* input = InputManager::getInstance();

    if (input->isKeyPressed(SDLK_a))
    {
        this->rotation += dt/6;

        if (input->isKeyPressed(SDLK_LSHIFT)) // Turbo rotation
            this->rotation += dt/3;
    }

    if (input->isKeyPressed(SDLK_d))
    {
        this->rotation -= dt/6;

        if (input->isKeyPressed(SDLK_LSHIFT)) // Turbo rotation
            this->rotation -= dt/3;
    }

    // Thrust frontward based on angle
    // We do this transformation because the ship starts pointing up
    // (instead of left, where the trigonometric circle starts)
    float angle = (this->rotation - 90) * PI/180;

    if (input->isKeyPressed(SDLK_w))
    {
        this->ax = this->acceleration * -1 * cos(angle);
        this->ay = this->acceleration *      sin(angle);
    }
    if (input->isKeyPressed(SDLK_s))
    {
        this->ax = -1 * this->acceleration * -1 * cos(angle);
        this->ay = -1 * this->acceleration *      sin(angle);
    }

    // -360 <= rotation <= 360
    this->rotation = ((int)rotation % 360);

    // if (this->rotation < 0)
    //     this->rotation = 360 - this->rotation;

    // accelerating
    this->vx += this->ax * dt;
    this->vy += this->ay * dt;

    // deaccelerating
    this->vx *= 0.81231;
    this->vy *= 0.88918;

    this->box->addX(this->vx * dt);
    this->box->addY(this->vy * dt);

    // Updating visible
    this->anim->update(dt);
    this->anim->rotoZoom(this->rotation);
}
void AccellObject::render(float cameraX, float cameraY)
{
    if (GameStateGame::showBoundingBoxes)
        this->boundingBox->render(cameraX, cameraY);

    this->anim->render(this->box->x - cameraX,
                       this->box->y - cameraY);
}

