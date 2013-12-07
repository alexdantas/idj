#include "Text.hpp"
#include "Log.hpp"

Text::Text(Font* font):
    font(font),
    surface(NULL),
    text(""),
    align(LEFT)
{ }
Text::~Text()
{
    SDL::deleteSurface(this->surface);
}
void Text::setText(std::string text)
{
    this->text = text;

    if (text != "")
        this->refresh();
}
void Text::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}
void Text::setAlignment(Alignment align)
{
    switch(align)
    {
    case CENTER:
        if (this->align != CENTER)
            this->x -= (this->getWidth()/2);
        break;
    case RIGHT:
        // TODO somehow
        break;
    case LEFT:
        // TODO also
        break;
    default:
        break;
    }
}
void Text::setFont(Font* font)
{
    this->font = font;

    if (this->text != "")
        this->refresh();
}
void Text::refresh()
{
    SDL::deleteSurface(this->surface);

    // Gets the visual surface containing the text.
    this->surface = (this->font->render(this->text));

	if (!(this->surface))
        Log::warning("TTF_RenderText_* Couldn't render text '" + this->text + "'");
}
void Text::render(float cameraX, float cameraY)
{
    if (!(this->surface)) return;

    SDL_Rect tmp;
    tmp.x = this->x - cameraX;
    tmp.y = this->y - cameraY;

    SDL::renderSurface(this->surface, NULL, &tmp);
}
float Text::getX()
{
    return this->x;
}
float Text::getY()
{
    return this->y;
}
int Text::getWidth()
{
	if (this->surface)
        return (this->surface->w);

	return 0;
}
int Text::getHeight()
{
	if (this->surface)
        return (this->surface->h);

	return 0;
}
int Text::getLines()
{
    // make some parser that checks the number of '\n's
    // on the text
    return 1;
}
int Text::getCols()
{
    return (this->text.length());
}

