#include "FollowerObject.hpp"
#include "Log.hpp"
#include "Graphics.hpp"
#include <cmath> // abs()

FollowerObject::FollowerObject(Sprite* sprite, float x, float y, int w, int h, int hp):
    GameObject(x, y, w, h),
    DamageableObject(hp),
    sprite(sprite),
    speedX(0),
    speedY(0),
    walkingSpeed(3.5)
{
    this->center = new Point(this->box->x + this->sprite->getWidth()/2,
                             this->box->y + this->sprite->getHeight()/2);
}
FollowerObject::~FollowerObject()
{
    // destroy everything
    if (this->center)
        delete this->center;
}
void FollowerObject::update(uint32_t dt)
{
    // Woops, empty command list!
    if (this->coordinatesQueue.size() == 0)
        return;

    Point* next = this->coordinatesQueue.front();

    // Number of pixels to tolerate on approximation of position.
    int tolerance = 5;

    // Has it arrived on it's destination yet?
    if ((this->center->x >= next->x - tolerance) &&
        (this->center->x <= next->x + tolerance) &&
        (this->center->y >= next->y - tolerance) &&
        (this->center->y <= next->y + tolerance))
    {
        // Destroy the first element of the queue
        this->coordinatesQueue.pop();
        delete next;
        Log::debug("FollowerObject::update Dequeue successful");

        // Please call update() again to follow new commands
        this->speedX = 0;
        this->speedY = 0;
        return;
    }

    // The movement of this thing seems complicated, so I'll explain
    // it a little better here.
    //
    // The idea was to make it move proportionally to the distance of
    // each axis.
    //
    // For example, suppose we want to move like this:
    //
    //  _________________        O = current object's position
    // | O                       X = where it want to go
    // |   `---                  - = object's path
    // |       `---              | = x axis' component
    // |           `----X        _ = y axis' component
    //
    // In the case above, the object wants to make a straight line to
    // it's destination. So it makes sense if the object moves faster
    // on the x axis and slower on the y.
    //
    // That's because the path on the first is bigger than the path on
    // the latter.
    //
    // So I divided both distances to get the proportion between them.
    // That, multiplied by `dx`, was the final speed!


    // Distance on each separate axis
    float distX = abs(this->center->x - next->x);
    float distY = abs(this->center->y - next->y);

    // Straight line distance
    float dist  = sqrt(pow(distX, 2) + pow(distY, 2));

    // How much speed per distance
    float proportion = (this->walkingSpeed)/dist;

    // The actual speed is the sum of two vectors, which
    // gives us this scalar formula.
    // Also, considering the time passed *dt*
    this->speedX = (proportion * ((next->x) - (this->center->x))) * (0.1*dt);
    this->speedY = (proportion * ((next->y) - (this->center->y))) * (0.1*dt);

    // Finally, refreshing everything.
    this->center->x += this->speedX;
    this->center->y += this->speedY;
    this->box->x    += this->speedX;
    this->box->y    += this->speedY;
}
void FollowerObject::render(float cameraX, float cameraY)
{
    if (!this->sprite) return;

    this->sprite->render(this->box->x - cameraX,
                         this->box->y - cameraY);
    this->renderQueueLines(cameraX, cameraY);
}
void FollowerObject::renderQueueLines(float cameraX, float cameraY)
{
    // Don't be scared, this method's quite simple
    // Just follow along calmly

    // To ease reading
    float cx = cameraX;
    float cy = cameraY;

    if (this->coordinatesQueue.size() == 0)
        return;

    // This is how the lines will be shown
    Color lineColor(255, 0, 255, 120);
    int   lineSpacing = 5;

    // Will use tmp queue to iterate to print onscreen
    std::queue<Point*, std::list<Point*> > tmpQueue;
    Point* currentPoint  = NULL;
    Point* previousPoint = NULL;

    // First line -- from follower to first command
    currentPoint = this->coordinatesQueue.front();
    this->coordinatesQueue.pop();

    Graphics::drawSpacedLine(Point(this->center->x - cx,  this->center->y - cy),
                             Point(currentPoint->x - cx,  currentPoint->y - cy),
                             lineColor,             lineSpacing);
    tmpQueue.push(currentPoint);

    // Lines of the rest of the commands
    while (this->coordinatesQueue.size() != 0)
    {
        previousPoint = currentPoint;
        currentPoint  = this->coordinatesQueue.front();
        this->coordinatesQueue.pop();

        Graphics::drawSpacedLine(Point(previousPoint->x - cx, previousPoint->y - cy),
                                 Point(currentPoint->x - cx,  currentPoint->y - cy),
                                 lineColor,             lineSpacing);

        tmpQueue.push(currentPoint);
    }
    this->coordinatesQueue = tmpQueue;
}
void FollowerObject::enqueueCommand(float x, float y)
{
    Point* point = new Point(x, y);
    this->coordinatesQueue.push(point);

    Log::debug("FollowerObject::enqueueCommand Successful");
}
bool FollowerObject::isMoving()
{
    if (this->coordinatesQueue.size() == 0)
        return false;

    return true;
}
void FollowerObject::empty()
{
    while (this->coordinatesQueue.size() != 0)
    {
        Point* point;

        point = this->coordinatesQueue.front();
        this->coordinatesQueue.pop();

        delete point;
    }
    Log::debug("FollowerObject::empty Succesful");
}

