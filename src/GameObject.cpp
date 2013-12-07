#include "GameObject.hpp"

// Almost a purely virtual class

GameObject::GameObject(float x, float y, int w, int h)
{
    this->box = new Rectangle(x, y, w, h);

    this->boundingBox = new RectBoundingBox(this->box);
}
GameObject::~GameObject()
{
    if (this->boundingBox) delete this->boundingBox;
    if (this->box)         delete this->box;
}
float GameObject::getX()
{
    return this->box->x;
}
float GameObject::getY()
{
    return this->box->y;
}
int GameObject::getWidth()
{
    return this->box->w;
}
int GameObject::getHeight()
{
    return this->box->h;
}
bool GameObject::collidedWith(GameObject* other)
{
    return (this->boundingBox->overlaps(other->boundingBox));
}

