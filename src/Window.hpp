#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <string>
#include <stdint.h> // uint32_t
#include "SDL.hpp"
#include "Color.hpp"

/// The main (and only) window of the program.
///
/// Wraps low-level SDL video functions that interfaces with the
/// Operational System's Window Manager.
///
/// Here we set things like fullscreen, window position, size, etc.
///
/// @note Most of these functions may fail horribly depending
///       on the OS! Do not rely on them too much.
///       The ones that may fail have their descriptions started
///       with _Tries to_.
///
class Window
{
public:

    /// Initializes the program's window with *width*, *height*
    /// and the text that should appear on the program's window
    /// (*windowCaption*) and when it's minimized
    /// (*minimizedWindowCaption*).
    static bool init(uint32_t width, uint32_t height, std::string windowCaption="", std::string minimizedWindowCaption="");

    /// Toggles fullscreen mode of the program's window.
    static bool toggleFullscreen();

    /// Tries to minimize the program's window.
    static bool minimize();

    /// Set Window icon to *filepath*.
    ///
    /// @note Win32 icons must be 32x32.
    static void setIcon(std::string filepath);

    /// Tries to resize the program's window to *width*/*height*.
    static void resize(uint32_t width, uint32_t height);

    /// Restarts the program's window.
    ///
    /// Good for applying internal settings or if something
    /// is messed up.
    static void restart();

    /// Tries to center the program's window position onscreen.
    static void center();

    /// Tries to set the program's window position to *x*/*y*.
    static void setPosition(int x, int y);

    /// Effectively draws everything that's onscreen.
    /// @note Need to be called constantly.
    static void refresh();

    /// Clears whole screen to the background color #bg_color.
    static void clear();

    /// Sets the background color to a RGB-formatted color.
    ///
    /// @note Affects clearScreen().
    static void setBackgroundColor(Color color=Color(0, 0, 0));

    static SDL_Surface* screen;
    static uint32_t width;
    static uint32_t height;
    static uint32_t flags;
    static bool isFullscreen;

private:
    /// Window caption (text that shows on the operational
    /// system's window).
    static std::string caption;

    /// Window caption when the window's minimized.
    static std::string minimizedCaption;

    /// The background color of the screen.
    /// @note Changeable only by setBackgroundColor().
    static uint32_t bg_color;
};

#endif //WINDOW_H_DEFINED

