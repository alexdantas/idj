#ifndef INPUTMANAGER_H_DEFINED
#define INPUTMANAGER_H_DEFINED

#include "SDL.hpp"

/// The number of keys on a keyboard.
//  This is the maximum number of any possible key, given by the
//  engine. We use it as the size of arrays to contain keys.
#define KEYBOARD_SIZE (SDLK_LAST + 1)

/// The number of buttons on a mouse.
//  The engine doesn't have a clear maximum number for a mouse key,
//  since it depends on the mouse model and manufacturer.
//
//  It's assumed to be 255, but usually we'll look only at the first 3
//  elements (mouse left, middle and right).
#define MOUSE_SIZE    (255)

/// Handles input through keyboard and mouse.
//  It's the interface between SDL-direct input calls.
//
//  @note This class is a Singleton.
//  Tips on how to implement a Singleton:
//  http://stackoverflow.com/a/271104
//
//  @warning I TRIED IMPLEMENTING A SINGLETON BUT IT JUST KEEPS
//  GETTING ERRORS ON PRIVATE CONSTRUCTORS ARRGHHH
//
//  This class *needs* to be update()d every frame.
//
//  It collects all input events and saves on it's internal
//  data structures.
//  When requested, returns info about the current state - for
//  example, is a key currently pressed? Is where's the mouse?
//
class InputManager
{
public:
    /// Returns the singleton instance of this class.
    //
    //  This assures that only a single instance of this class is
    //  created at any point on the game.
    static InputManager* getInstance();

    /// Updates the entire game input state.
    ///
    /// This method deals with very low-level SDL calls.
    ///
    /// But what it _really_ does is check the keyboard/mouse for
    /// any signs at all (keys down, keys up, mouse pressed,
    /// mouse X...) and update internal variables that reflect
    /// that.
    void update(float cameraX=0, float cameraY=0);

    /// Tells if the keyboard *key* was released just now.
    //
    //  To see all possibilities, see isKeyPressed().
    bool isKeyDown(int key);

    /// Tells if the keyboard *key* was pressed just now.
    //
    //  To see all possibilities, see isKeyPressed().
    bool isKeyUp(int key);

    /// Tells if the mouse *button* was released just now.
    //
    //  To see all possibilities, see isMousePressed().
    bool isMouseDown(uint8_t button);

    /// Tells if the mouse *button* was pressed just now.
    //
    //  To see all possibilities, see isMousePressed().
    bool isMouseUp(uint8_t button);

    /// Tells if the *key* is currently being pressed.
    //
    //  To see all available keys, visit this site:
    //  http://wiki.libsdl.org/moin.fcg/SDL_Keycode
    bool isKeyPressed(int key);

    /// Tells if the mouse *button* is currently being pressed.
    //
    //  ## Possible options are
    //  SDL_BUTTON_LEFT:   left mouse button
    //  SDL_BUTTON_MIDDLE: middle mouse button
    //  SDL_BUTTON_RIGHT:  right mouse button
    bool isMousePressed(uint8_t button);

    /// Tells if the user asked the game to quit
    /// (Alt+F4 or close button).
    bool quitRequested();

    /// Returns the current mouse X position.
    int getMouseX();

    /// Returns the current mouse Y position.
    int getMouseY();

    /// Tells if the mouse's currently inside the rectangle
    //  specified by #x, #y, #w and #h.
    bool isMouseInside(int x, int y, int w, int h);

    InputManager();

    // Removing copy-constructor and assignment operator.
    InputManager(InputManager const&) {};
    void operator=(InputManager const&) {};

private:
    /// Current single instance of the class.
    static InputManager* instance;

    /// Saves SDL internal mouse state.
    uint8_t  mouse;

    /// Saves SDL internal keyboard state.
    uint8_t* keyboard;

    /// Current mouse X position.
    int  mouseX;

    /// Current mouse Y position.
    int  mouseY;

    /// Saves which keys are currently down.
    bool keyDown[KEYBOARD_SIZE];

    /// Saves which keys are currently up.
    bool keyUp[KEYBOARD_SIZE];

    /// Saves which mouse buttons are currently down.
    bool mouseDown[MOUSE_SIZE];

    /// Saves which mouse buttons are currently up.
    bool mouseUp[MOUSE_SIZE];

    /// Tells if we must quit the game.
    bool will_quit;
};


#endif /* INPUTMANAGER_H_DEFINED */
