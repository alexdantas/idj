#include "SplashScreen.hpp"

SplashScreen::SplashScreen(std::string imagePath)
{
    this->screen = SDL_SetVideoMode(200, 200, 0, SDL_NOFRAME);

    this->image = SDL::loadBMP(imagePath);
    SDL::renderSurface(image);

    SDL_Flip(this->screen);
}
void SplashScreen::exit()
{
    SDL::deleteSurface(this->image);
}



