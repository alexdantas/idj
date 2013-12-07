#ifndef CAMERA_H_DEFINED
#define CAMERA_H_DEFINED

#include "stdint.h"

class Camera
{
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Camera(float x, float y, int w, int h, float scrollSpeed);

    /// Updates current camera position according to it's scroll speed.
    //  @note #dt is the delta time from last frame.
    void update(uint32_t dt);

    float getX();
    float getY();
    int   getWidth();
    int   getHeight();

    /// Centers the camera on *x* and *y*.
    void centerOn(int x, int y);

    /// Stops all current movements on the camera.
    void stop();

    /// Sets the speed that the camera will scroll at a time.
    void setScrollSpeed(float speed);

    void increaseScrollSpeedBy(float acc);
    void decreaseScrollSpeedBy(float acc);

    /// Commands the camera to start scrolling to direction #dir.
    void scroll(Direction dir);

    /// Commands the camera to stop scrolling to direction #dir.
    void unscroll(Direction dir);

private:
    /// Current camera position on the x-axis.
    float x;

    /// Current camera position on the y-axis.
    float y;

    int w;
    int h;

    /// Current speed that the camera is is crolling right now on the x-axis.
    float speedX;

    /// Current speed that the camera is is crolling right now on the y-axis.
    float speedY;

    /// Current speed (pixels) that the camera moves each step.
    float scrollSpeed;
};

#endif /* CAMERA_H_DEFINED */
