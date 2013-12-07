#ifndef GAMESTATEGAMEOVER_H_DEFINED
#define GAMESTATEGAMEOVER_H_DEFINED

#include "GameState.hpp"
#include "Font.hpp"
#include "Text.hpp"
#include "Animation.hpp"
#include "Explosion.hpp"
#include "Music.hpp"

/// Shows that depressing screen when the player loses.
class GameStateGameOver: public GameState
{
public:
    GameStateGameOver();

    /// Constructs everything necessary for the screen.
    void load(int stack=0);

    /// Destroys anything builded during the screen.
    int unload();

    /// Updates all possible things on the screen.
    ///
    /// @return A status code indicating what to do (should we
    ///         change states/quit the game?). The codes are
    ///         defined on GameState.hpp.
    int update(uint32_t dt);

    /// Shows everything onscreen;
    void render();

private:
    Font* font;
    Text* text1;
    Text* text2;
    Animation* explosionAnim;
    Explosion* explosion;
    Music* music;
};

#endif //GAMESTATEGAMEOVER_H_DEFINED

