#ifndef FOLLOWEROBJECT_H_DEFINED
#define FOLLOWEROBJECT_H_DEFINED

#include <queue>
#include <list>
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Shapes.hpp"
#include "DamageableObject.hpp"

/// Creates an object that will follow wherever you tell it to.
//
//  Internally it uses a queue of commands.
//
//  Firstly, it's stopped. If you send a command to it, will do.
//  If other commands are sent during the execution of the first,
//  they'll be queued on a 'first-come-first-serve'-basis.
class FollowerObject: public GameObject,
                      public DamageableObject
{
public:
    /// New object with initial positions #x, #y and #sprite appearance.
    FollowerObject(Sprite* sprite, float x, float y, int w, int h, int hp);

    virtual ~FollowerObject();

    /// Updates the FollowerObject's position ans speed.
    //  If there are no commands to do, does nothing.
    void update(uint32_t dt);

    /// Prints the FollowerObject onscreen.
    //  @note Prints it based on it's #center position, not the
    //        top-left Sprite position.
    void render(float cameraX, float cameraY);

    /// Prints the command queue lines onscreen.
    void renderQueueLines(float cameraX, float cameraY);

    /// Orders FollowerObject to move to #x and #y.
    //  If there are any other commands being processed, this is
    //  inserted on a 'first-come-first-serve' queue.
    void enqueueCommand(float x, float y);

    /// Tells if the FollowerObject is currently moving.
    bool isMoving();

    void empty();

private:
    /// The appearance of the FollowerObject.
    Sprite* sprite;

    /// Object's center position (based on the Sprite's sizes).
    Point*  center;

    float   speedX;  ///< Current speed on the X axis.
    float   speedY;  ///< Current speed on the Y axis.

    float   walkingSpeed; ///< Speed of movement

    /// Queue of commands to follow.
    //  Using a queue implemented with a list. That's because
    //  expansibility is more important than speed of access on this
    //  case.
    std::queue<Point*, std::list<Point*> > coordinatesQueue;
};


#endif /* FOLLOWEROBJECT_H_DEFINED */
