
#ifndef ANIMATION_H_DEFINED
#define ANIMATION_H_DEFINED

#include "SDL.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Color.hpp"

/// Animate sprites based on a spritesheet.
///
/// This uses class *Sprite* to show an animation.
/// Basically, it opens a large image and displays small pieces
/// of it on a steady speed to simulate movement.
///
/// Don't worry, we've got timing covered. We use class *Timer* to
/// keep track of when to switch frames. Also, whenever we get to the
/// end of the animation, it'll restart.
///
/// The only thing you need to worry is calling the functions
/// *update()* and *render()*.
/// Also, you should refresh the screen regularly to see any changes.
///
/// @note This class assumes you've got all sprites on a single line.
///       It does _not_ work with multi-lined spritesheets.
/// ## Usage
///     Animation anim("path/to/image.png", spriteWidth, spriteHeight, numberOfFrames, delay);
///     anim.start()
///     ///on a loop...
///         anim.update();
///         anim.render(x, y);
///
/// ## For developers
/// This class is very coupled with SDL, because it uses SDL's
/// representation of rectangles and sprites.
/// For inclusion on your project, you _must_ include *Sprite* and
/// modify some methods there to suit your engine.
///
class Animation: public Sprite
{
public:
    /// Starts an animation from the image on *filepath*, with *ammount*
    /// sprites, with *framerate* frames per second.
    ///
    /// @note If *framerate* is zero, will not update at all
    /// (useful for a standing animation, for example).
    Animation(std::string filepath, int ammount=1, int framerate=0, int loops=-1);

    /// Updates animation.
    ///
    /// Checks if it's time to change sprites and does it if necessary.
    virtual void update(uint32_t dt);

    /// Starts a new animation from the image on *filepath*, with *ammount*
    /// sprites and framerate *framerate*.
    ///
    /// @note If *framerate* is zero, will not update at all
    ///       (useful for a standing animation, for example).
    void setAnimation(std::string filepath, int ammount, int framerate=0, int loops=-1);

    /// Actually loads into memory all the stuff.
    ///
    /// @note Don't call this unless you want to reload the image -
    ///       it's already taken care of.
    // bool load();


    // The following functions shouldn't be called unless you really
    // know what you're doing.

    /// Forces animation to next frame.
    ///
    /// If it ever gets to the last, will restart.
    void nextFrame();

    /// Forces animation to previous frame.
    ///
    /// If it ever gets past the first frame, will go to the last.
    void prevFrame();

    /// Forces animation to the first frame.
    void firstFrame();

    /// Forces animation to the last frame.
    void lastFrame();

    /// Forces animation to go to *frame*.
    ///
    /// If it's not on the acceptable range, it does nothing.
    ///
    /// @note Frame counts start at zero!
    void goTo(int frame);

    /// Sets the current framerate of animation to *framerate* miliseconds
    /// (_1/1000_ of a second).
    void setFramerate(int framerate);

    /// Starts the animation, making all necessary preparations.
    ///
    /// Innefective if already started.
    void start();

    /// Stops the animation
    ///
    /// Innefective if already stopped.
    void stop();

    /// Restarts (stop and start) the animation.
    void restart();

    /// Tells if the animation has already started.
    bool isRunning();

    void setLoopAmmount(int times=-1);

private:
    /// How many frames per second the animation has.
    ///
    /// The time between frames is (1/framerate).
    unsigned int framerate;

    /// Tells if the animation is running.
    bool running;

    /// Index of the current frame of animation.
    int curFrame;

    /// Index of the last frame of animation.
    int maxFrame;

    /// Timer that controls the animation flow.
    Timer timer;

    /// The filepath of the current image.
    std::string filepath;

    /// How many loops the animation will do before ending.
    int loops;

    /// How many times the animation has already looped.
    int timesLooped;
};

#endif /* ANIMATION_H_DEFINED */
