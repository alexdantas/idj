#include "Explosion.hpp"
#include "Log.hpp"

Explosion::Explosion(Animation* animation, int timesExploding):
    GameObject(0, 0, animation->getWidth(), animation->getHeight()),
    animation(animation),
    exploding(false)
{
    this->animation->setLoopAmmount(timesExploding);
}
void Explosion::update(uint32_t dt)
{
    if (!(this->exploding))
        return;

    this->animation->update(dt);

    if (!(this->animation->isRunning()))
    {
        this->exploding = false;
        Log::debug("Explosion::update Stopped");
    }
}
void Explosion::render(float cameraX, float cameraY)
{
    if (!(this->exploding))
        return;

    this->animation->render(this->box->x - cameraX,
                            this->box->y - cameraY);
}
void Explosion::explodeAt(float x, float y)
{
    this->exploding = true;

    // Centering explosion on x/y
    this->box->x = (x - this->box->w/2);
    this->box->y = (y - this->box->h/2);

    this->animation->restart();
    Log::debug("Explosion::explodeAt (" +
               SDL::intToString(x) + ", " +
               SDL::intToString(y) + ")");
}
bool Explosion::isExploding()
{
    return (this->exploding);
}

