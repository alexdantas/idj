#ifndef STATEMANAGER_H_DEFINED
#define STATEMANAGER_H_DEFINED

#include "GameState.hpp"

/// Giga-class that handles all game states.
///
/// Game states are possible game configurations.
/// Like `MainMenu`, `GameOver`, `OptionsMenu`, etc.
class StateManager
{
public:
    /// Initializes pretty much everything.
    StateManager(int width, int height);

    virtual ~StateManager();

    /// Main entry point and game loop.
    ///
    /// This is where it all happens.
    void run();

private:
    /// Current game state - defines what will actually happen.
    GameState* currentState;

    /// Shared information between states.
    ///
    /// If a state want to share something with another, it should
    /// return a value that will be stored right here.
    int sharedInfo;
};

#endif /* STATEMANAGER_H_DEFINED */
