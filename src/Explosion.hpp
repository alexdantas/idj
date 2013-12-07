#ifndef EXPLOSION_H_DEFINED
#define EXPLOSION_H_DEFINED

#include "GameObject.hpp"
#include "Animation.hpp"

/// Explosion that can be added anytime anywhere.
///
/// This is a general class and works with any kind of explosion
/// you may want to throw at the screen.
///
/// It depends on the *Animation* class, because that's where
/// you'll set up the explosion's sprites. It's up to you to
/// initialize the animation and destroy if later.
///
/// ## Usage
///     Animation anim("img/explosion.png", 5, 30);
///     Explosion expl(&anim);
///
///     expl.explodeAt(20, 21);
///
///         // During a loop
///         expl.render();
///         expl.update(delta);
///
class Explosion: public GameObject
{
public:
    /// Creates an explosion with *animation* and the ammount
    /// of times it explodes (by default, 1).
    ///
    /// @note To actually explode, call *explodeAt()*.
    Explosion(Animation* animation, int timesExploding=1);

    /// If the explosion is occurring, shows it onscreen.
    ///
    /// @note Must be called on a game loop to make sure it
    ///       animates alright.
    void render(float cameraX=0, float cameraY=0);

    /// Updates explosion's internal state
    ///
    /// @note Must be called on a game loop to make sure it
    ///       updates alright.
    void update(uint32_t dt);

    /// Actually starts exploding at the center point *x*/*y*.
    ///
    /// @note This method is *nonblocking* - if you call it
    ///       multiple times, it will keep restarting the
    ///       explosion.
    void explodeAt(float x, float y);

    /// Tells if the explosion is currently happening.
    bool isExploding();

private:

    /// Explosion's animation (sprite, etc).
    Animation* animation;

    /// Flag to tell if it's exploding.
    bool exploding;
};

#endif /* EXPLOSION_H_DEFINED */
