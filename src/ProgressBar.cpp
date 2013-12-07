#include "ProgressBar.hpp"

ProgressBar::ProgressBar(int width, int height, int max, int starting):
    maxValue(max),
    currentValue(starting),
    width(width),
    height(height),
    isComplete(false),
    isZero(true),
    surface(NULL)
{
    this->surface = SDL::newSurface(width, height);

    if (this->currentValue != 0)
        this->isZero = false;

    // applying default colors
    this->setForegroundColor();
    this->setBackgroundColor();
}
ProgressBar::~ProgressBar()
{
    SDL::deleteSurface(this->surface);
}
void ProgressBar::increase(int ammount)
{
    this->currentValue += ammount;

    if (this->currentValue >= this->maxValue)
    {
        this->isComplete   = true;
        this->currentValue = this->maxValue;
    }

    if (this->currentValue != 0)
        this->isZero = false;
}
void ProgressBar::decrease(int ammount)
{
    this->currentValue -= ammount;

    if (this->currentValue < 0)
        this->currentValue = 0;

    if (this->currentValue == 0)
        this->isZero = true;

}

bool ProgressBar::isFull()
{
    return (this->isComplete);
}
bool ProgressBar::isEmpty()
{
    return (this->isZero);
}
void ProgressBar::render(int x, int y)
{
    int fullRectWidth  = (this->width/this->maxValue) * this->currentValue;
    int emptyRectWidth = (this->width - fullRectWidth);

    // TODO somehow make this function on SDL.hpp wrapper
    // NOT modular thinking here
    SDL_Rect tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.w = fullRectWidth;
    tmp.h = this->height;

    if (this->currentValue != 0)
        SDL_FillRect(this->surface, &tmp, SDL::convertColorFormat(this->filledColor));

    tmp.x = fullRectWidth;
    tmp.w = emptyRectWidth;

    if (this->currentValue != this->maxValue)
        SDL_FillRect(this->surface, &tmp, SDL::convertColorFormat(this->emptyColor));

    // Now, actually printing the progress bar on the "main screen"
    tmp.x = x;
    tmp.y = y;
    SDL::renderSurface(this->surface, NULL, &tmp);
}
void ProgressBar::setBackgroundColor(Color color)
{
    this->emptyColor = color;
}
void ProgressBar::setForegroundColor(Color color)
{
    this->filledColor = color;
}


