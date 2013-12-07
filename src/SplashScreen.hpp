#ifndef SPLASHSCREEN_H_DEFINED
#define SPLASHSCREEN_H_DEFINED

#include "SDL.hpp"

/// TODO this class is NOT DONE YET
/// TODO do NOT use it
///
/// A screen without borders that's generally shown at
/// the startup of a program (when things are loading).
///
class SplashScreen
{
public:
    SplashScreen(std::string imagePath);

    void exit();

private:
    SDL_Surface* screen;
    SDL_Surface* image;
};

#endif //SPLASHSCREEN_H_DEFINED

