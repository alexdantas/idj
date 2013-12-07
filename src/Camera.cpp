#include "Camera.hpp"

Camera::Camera(float x, float y, int w, int h, float scrollSpeed)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    this->stop();

    this->scrollSpeed = scrollSpeed;
}
float Camera::getX()
{
    return this->x;
}
float Camera::getY()
{
    return this->y;
}
int Camera::getWidth()
{
    return this->w;
}
int Camera::getHeight()
{
    return this->h;
}
void Camera::update(uint32_t dt)
{
    this->x += (this->speedX) * dt;
    this->y += (this->speedY) * dt;
}
void Camera::centerOn(int x, int y)
{
    this->x = x - this->w/2;
    this->y = y - this->h/2;
}
void Camera::setScrollSpeed(float speed)
{
    this->scrollSpeed = speed;
}
void Camera::increaseScrollSpeedBy(float acc)
{
    this->scrollSpeed += acc;
}
void Camera::decreaseScrollSpeedBy(float acc)
{
    this->scrollSpeed -= acc;
}
void Camera::scroll(Direction dir)
{
    switch (dir)
    {
    case LEFT:  this->speedX -= this->scrollSpeed; break;
    case RIGHT: this->speedX += this->scrollSpeed; break;
    case UP:    this->speedY -= this->scrollSpeed; break;
    case DOWN:  this->speedY += this->scrollSpeed; break;
    }
}
void Camera::unscroll(Direction dir)
{
    switch (dir)
    {
    case LEFT:  this->speedX += this->scrollSpeed; break;
    case RIGHT: this->speedX -= this->scrollSpeed; break;
    case UP:    this->speedY += this->scrollSpeed; break;
    case DOWN:  this->speedY -= this->scrollSpeed; break;
    }
}
void Camera::stop()
{
    this->speedX = 0;
    this->speedY = 0;
}


