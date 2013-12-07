#include "Color.hpp"
#include "SDL.hpp"

Color::Color()
    : red(0), green(0), blue(0), alpha(255)
{
}

Color::Color(int color)
{
    this->red = (color >> 16) & 0xFF;
    this->red = (color >>  8) & 0xFF;
    this->red =  color        & 0xFF;
    this->alpha = 255;
}
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : red(r), green(g), blue(b), alpha(a)
{
}
Color Color::operator+(const Color& color) const
{
    int tmp  = 0;

    uint8_t tmpR = 0;
    tmp = this->red + color.red;
    if (tmp > 255) tmpR = 255;
    if (tmp < 0)   tmpR = 0;

    uint8_t tmpG = 0;
    tmp = this->green + color.green;
    if (tmp > 255) tmpG = 255;
    if (tmp < 0)   tmpG = 0;

    uint8_t tmpB = 0;
    tmp = this->blue + color.blue;
    if (tmp > 255) tmpB = 255;
    if (tmp < 0)   tmpB = 0;

    uint8_t tmpA = 255;
    if (this->alpha == color.alpha)
        tmpA = this->alpha;

    Color result(tmpR, tmpG, tmpB, tmpA);
    return result;
}
Color Color::operator-(const Color& color) const
{
    int tmp  = 0;

    uint8_t tmpR = 0;
    tmp = this->red - color.red;
    if (tmp > 255) tmpR = 255;
    if (tmp < 0)   tmpR = 0;

    uint8_t tmpG = 0;
    tmp = this->green - color.green;
    if (tmp > 255) tmpG = 255;
    if (tmp < 0)   tmpG = 0;

    uint8_t tmpB = 0;
    tmp = this->blue - color.blue;
    if (tmp > 255) tmpB = 255;
    if (tmp < 0)   tmpB = 0;

    uint8_t tmpA = 255;
    if (this->alpha == color.alpha)
        tmpA = this->alpha;

    Color result(tmpR, tmpG, tmpB, tmpA);
    return result;
}
bool Color::operator==(const Color& color) const
{
    return ((this->red   == color.red)   &&
            (this->green == color.green) &&
            (this->blue  == color.blue)  &&
            (this->alpha == color.alpha));
}
bool Color::operator!=(const Color& color) const
{
    return ((this->red   != color.red)   &&
            (this->green != color.green) &&
            (this->blue  != color.blue)  &&
            (this->alpha != color.alpha));
}
uint8_t Color::r()
{
    return this->red;
}
uint8_t Color::g()
{
    return this->green;
}
uint8_t Color::b()
{
    return this->blue;
}
uint8_t Color::a()
{
    return this->alpha;
}
void Color::randomize()
{
    this->red   = SDL::randomNumberBetween(0, 255);
    this->green = SDL::randomNumberBetween(0, 255);
    this->blue  = SDL::randomNumberBetween(0, 255);
}
void Color::randomizeAlpha()
{
    this->alpha = SDL::randomNumberBetween(0, 255);
}

