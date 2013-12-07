#ifndef SDL_H_DEFINED
#define SDL_H_DEFINED

#include <string>
#include <iostream>
#include <stdint.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_framerate.h"
#include "Timer.hpp"
#include "Color.hpp"
#include "Shapes.hpp"

// Shuts up the compiler about unused parameters.
#define UNUSED(x) ((void)(x))

/// Big wrapper class thath handles all direct SDL
/// calls (except for video).
///
/// For a video-oriented SDL wrapper, see Window.
///
/// SDL object-oriented wrapper. Deals with most SDL subsystems
/// (TTF, Mixer, IMG...).
///
/// Most of the methods inside report errors to stdout with the Log
/// class.
///
class SDL
{
public:
    /// Starts all things related to SDL (except for video).
    ///
    /// The constructor only allocates stuff, here's where the
    /// action begins.
    ///
    /// @return true if OK, false if something's wrong
    /// @note   I encourage you to call `delete` if this
    ///         returns false.
    /// @see    Window
    ///
    static bool init(uint32_t frameRate=30);

    /// Destroys anything related to SDL.
    static void exit();

    /// Start the audio subsystem.
    ///
    /// This is already taken care of for you.
    static bool initAudio();

    /// IMAGE METHODS

    /// Creates a new empty surface with *width* and *height*.
    static SDL_Surface* newSurface(int width, int height);

    /// Safely delete a surface (NULL-check).
    static void deleteSurface(SDL_Surface* surface);

    /// Places the surface *source* (on *position* and *cropped*) onscreen.
    /// @note Need to call refreshScreen() after.
    static void renderSurface(SDL_Surface* source, SDL_Rect* crop=NULL, SDL_Rect* position=NULL);

    /// Loads image specified by *filename*, trying to optimize it to
    /// show onscreen if *optimize* is true.
    /// @return The pointer to it if OK, NULL if something strange happened.
    /// @note   Remember to call freeImage() if loaded sucessfully.
    static SDL_Surface* loadImage(std::string filename, bool optimize=true);

    /// Cleans *image* from memory, safe-checking if NULL.
    static void freeImage(SDL_Surface* image);

    /// Loads a BMP image specified by *filename*.
    ///
    /// This is way simpler and less memory-intensive than *loadImage*.
    /// Good for quick-to-use images (like on a splash screen).
    static SDL_Surface* loadBMP(std::string filename);

    /// Prints lots of info about the current system on stdout.
    static void printSystemInfo();

    /// Converts *color* to SDL's specific color format, used on a lot
    /// of SDL's low-level functions.
    static uint32_t convertColorFormat(Color color);

    /// AUDIO METHODS

    /// Tells if we're currently supporting audio.
    static bool hasAudio();

    /// Tells if there's any music playing anywhere on the game.
    static bool musicPlaying();

    /// Tells if there's any paused music anywhere on the game.
    static bool musicPaused();

    /// Pauses any music that could be playing.
    /// It safe-checks so you don't have to.
    static void pauseMusic();

    /// Resumes any music that may be paused.
    /// It safe-checks so you don't have to.
    static void resumeMusic();

    /// Stops any music that may be playing or paused.
    /// It safe-checks so you don't have to.
    /// @note Any subsequent calls to pauseMusic() and resumeMusic()
    ///       will be ignored.
    static void stopMusic();

    /// FRAMERATE METHODS

    /// Returns the ammount of time each frame should have according
    /// to the framerate.
    static Uint32 getFramerateDelay();

    /// Waits as long as needed to keep the framerate, if necessary.
    /// @note Sometimes it will not sleep at all.
    static void framerateWait();

    /// Returns the ammount of time the last frame had.
    static uint32_t getDelta();

    /// Misc/Fun METHODS

    /// Pauses the whole program for *delay* milliseconds (1/1000 of a second).
    static void delay_ms(int delay);

    /// Returns a random integer between *min* and *max* (inclusive).
    static int randomNumberBetween(int min, int max);

    /// Hides the mouse cursor.
    static void hideCursor();

    /// Shows the mouse cursor if hidden.
    static void showCursor();

    /// Toggles The cursor's visible state (shown/hidden).
    static void toggleCursor();

    /// Ejects the CD tray.
    /// This function fails if there's not a default CD-ROM drive.
    /// @return Bool representing success/fail.
    static bool ejectCDTray();

    /// Grabs (almost) all input from keyboard and mouse to the Window.
    static void grabInput();

    /// Releases the exclusive input from keyboard and mouse to the Window.
    static void releaseInput();

    /// Toggles the input-grabbed state.
    ///
    /// @see grabInput()
    /// @see releaseInput()
    static void toggleGrabInput();

    /// Warps the mouse to the new position *x*/*y*.
    ///
    /// @note It generates a mouse motion event - just like if the
    ///       user had done it.
    static void setMousePosition(uint16_t x, uint16_t y);

    // Weird methods that shouldn't be here

    /// Tells if the *key* can be printed onscreen (not a control key).
    /// If a key is visible according to the ASCII table.
    static bool isPrintable(SDLKey key);

    /// Converts an integer to string and return it.
    /// This is harder than it seems. In C all you had to do was call
    /// atoi(), but now it's not part of the C++ standard.
    /// So we need to create a string stream and do some mumbo-jumbo
    /// stuff to it.
    static std::string intToString(int num);

    /// Rotates and/or zooms surface *src*, with *angle*, *scaleX* and
    /// *scaleY*.
    static SDL_Surface* rotoZoom(SDL_Surface* surface, float angle, float scaleX=1.0, float scaleY=1.0);

    /// Returns a new copy of the *original* surface, clipped with
    /// sizes on *clip*.
    static SDL_Surface* clip(SDL_Surface* original, SDL_Rect* clip);

private:
    /// The framerate. By default, 60 frames per second.
    static uint32_t framerate;

    /// How much time each frame must have according to the framerate.
    static uint32_t framerate_delay;

    /// The timer that keeps calculating the delta between frames.
    static Timer  framerate_timer;

    /// How much time has passed between this and last frame (milisseconds).
    static uint32_t frame_delta;

    /// Tells if we're started the audio interface.
    /// The game musn't crash because of it, so it's ok if this is false.
    static bool startedAudio;

    /// SDL's internal data structure to deal with FPS.
    static FPSmanager fpsManager;
};

#endif /* SDL_H_DEFINED */
