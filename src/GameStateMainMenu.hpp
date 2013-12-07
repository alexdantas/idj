#ifndef GAMESTATEMAINMENU_H_DEFINED
#define GAMESTATEMAINMENU_H_DEFINED

#include "GameState.hpp"
#include "Font.hpp"
#include "Music.hpp"
#include "Text.hpp"
#include "Menu.hpp"
#include "Sprite.hpp"

/// Everything that happens on the main menu.
class GameStateMainMenu: public GameState
{
public:
    GameStateMainMenu();
    virtual ~GameStateMainMenu();

    /// Constructs everything necessary for the menu.
    void load(int stack=0);

    /// Destroys anything builded during the menu.
    int unload();

    /// Updates all possible things on the menu.
    ///
    /// @return A status code indicating what t odo (should we
    ///         change states/quit the game?). The codes are
    ///         defined on GameState.hpp.
    int update(uint32_t dt);

    /// Shows everything onscreen;
    void render();

private:
    Font* font;       ///< How the menu will show onscreen.
    Font* hiliteFont; ///< How menu's current item will be shown.
    Music* music;     ///< Menu's background music.

    Menu* menu;       ///< The actual game menu.

    Sprite* bg;       ///< The background image.
};

#endif //GAMESTATEMAINMENU_H_DEFINED

