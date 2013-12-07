#ifndef GAMESTATE_H_DEFINED
#define GAMESTATE_H_DEFINED

// I only need `uint32_t` because of SDL's internal timer
// structure.
#include <stdint.h>

/// Abstract definition of a game state.
///
/// Think of it as a... well, state the game has. Like, when the
/// game starts, it shows the main menu (a state). From there,
/// the player can start the game (another state) and, show
/// the pause menu (even another state).
/// Examples include the game over screen, high score screen,
/// cutscenes, etc.
///
/// Every state will inherit from this one and basically will
/// need to load(), update(), render() and unload() itself.
///
/// Each state communicates via return values of the update()
/// method. If, for instance, the player dies during the game,
/// it should return *GAME_OVER* or *QUIT*.
///
/// Then, the StateManager would know what to do.
///
class GameState
{
public:
    /// All possible transitions between states.
    enum State
    {
        QUIT, CONTINUE, MAIN_MENU, GAME_START, GAME_OVER
    };

    // Left this here just because.
    virtual ~GameState() {};

    /// Where every state initializes resources.
    virtual void load(int stack=0) = 0;

    /// Where every state destroys it's resources.
    virtual int unload() = 0;

    /// Called every frame, where states calculate everything.
    virtual int update(uint32_t dt) = 0;

    /// Called every frame, where states draw stuff on screen.
    virtual void render() = 0;

private:
};

#endif //GAMESTATE_H_DEFINED

