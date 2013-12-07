#include "Font.hpp"
#include "Log.hpp"

Font::Font(std::string filepath, int size, RenderType renderType, Color color):
    font(NULL),
    surface(NULL)
{
    this->setRenderType(renderType);
	this->setFont(filepath, size);
	this->setColor(color);

    this->load();
}
Font::~Font()
{
//	Why does this gives me a Segmentation Fault?
//	if (this->font)	   TTF_CloseFont(this->font);
	if (this->surface) SDL_FreeSurface(this->surface);
}
bool Font::load()
{
	if (this->font) TTF_CloseFont(this->font);

	this->font = TTF_OpenFont(this->filepath.c_str(), this->size);
	if (!this->font)
    {
        Log::error("Couldn't load font '" + this->filepath + "': " +
                   std::string(SDL_GetError()));
		return false;
    }

	return true;
}
void Font::setFont(std::string filepath, int size)
{
	this->filepath = filepath;
	this->size = size;
    this->load();
}
void Font::setColor(Color color)
{
	this->color = color;
}
void Font::setRenderType(RenderType renderType)
{
    this->renderType = renderType;
}
bool Font::print(int x, int y, std::string text, FontStyle style)
{
    if (!this->font) return false;

    // Getting FONT style
	int cur_style = TTF_STYLE_NORMAL;

    switch (style)
    {
    case BOLD:      cur_style = TTF_STYLE_BOLD;      break;
    case ITALIC:    cur_style = TTF_STYLE_ITALIC;    break;
    case UNDERLINE: cur_style = TTF_STYLE_UNDERLINE; break;
    case NORMAL: default: break;
    }

	// we can use | to set several styles
	// maybe i should create a nicer interface to it
	TTF_SetFontStyle(this->font, cur_style);

    // Getting SURFACE style
	if (this->surface) SDL_FreeSurface(this->surface);

	SDL_Color tmpColor;
	tmpColor.r = this->color.r();
	tmpColor.g = this->color.g();
	tmpColor.b = this->color.b();

    const char* ctext = text.c_str();
    switch (this->renderType)
    {
    case BLENDED:
        this->surface = TTF_RenderText_Blended(this->font, ctext, tmpColor);
        break;
    case SOLID: default:
        this->surface = TTF_RenderText_Solid(this->font, ctext, tmpColor);
        break;
    }
	if (!this->surface)
    {
        Log::warning("TTF_RenderText_* Couldn't render text '" + text + "'");
		return false;
    }

	// Getting WHERE to render
	SDL_Rect tmpRect;
	tmpRect.x = x;
	tmpRect.y = y;

    // Actually rendering
	SDL::renderSurface(this->surface, NULL, &tmpRect);
	return true;
}
SDL_Surface* Font::render(std::string text)
{
	SDL_Color tmpColor;
	tmpColor.r = this->color.r();
	tmpColor.g = this->color.g();
	tmpColor.b = this->color.b();

    return (TTF_RenderText_Solid(this->font, text.c_str(), tmpColor));
}
// I made these based on this tutorial:
// http://www.sdltutorials.com/sdl-ttf
// but it doesn't seem to be working, DAMN
//
// void Font::setOutline(int size)
// {
//	TTF_SetFontOutline(this->font, size);
// }
// int	Font::getOutline()
// {
//	   TTF_GetFontOutline(this->font);
// }
// void Font::resetOutline()
// {
//	   this->setOutline(0);
// }
