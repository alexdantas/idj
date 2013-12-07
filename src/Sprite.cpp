#include "Sprite.hpp"
#include "Log.hpp"

Sprite::Sprite(std::string filename):
    filename(filename),
    surface(NULL),
    surfaceRotoZoom(NULL),
    clipRect(NULL),
    angle(0),
    scaleX(1.0),
    scaleY(1.0)
{
    this->load();
}
Sprite::~Sprite()
{
    this->restore();
    if (this->surface) SDL_FreeSurface(this->surface);
    if (this->clipRect) delete this->clipRect;
}
void Sprite::setFilename(std::string newFilename)
{
    this->filename = newFilename;
}
bool Sprite::load()
{
    if (!(this->surface))
    {
        SDL_FreeSurface(this->surface);
        this->surface = NULL;
    }

    this->surface = SDL::loadImage(this->filename);
    if (!(this->surface))
    {
        Log::error("Sprite::load Failed on '" + this->filename + "'");
        return false;
    }

    // Will print image at it's original size
    this->crop(0, 0, (this->surface->w), (this->surface->h));

    Log::debug("Sprite::load '" + this->filename + "'");
    return true;
}
void Sprite::crop(int x, int y, int w, int h)
{
    if (!(this->clipRect))
        this->clipRect = new SDL_Rect;

    this->clipRect->x = x;
    this->clipRect->y = y;
    this->clipRect->w = w;
    this->clipRect->h = h;
}
void Sprite::render(int x, int y)
{
    // tells where to render
    SDL_Rect tmpRect;
    tmpRect.x = x;
    tmpRect.y = y;

    if (this->surfaceRotoZoom)
    {
        if (this->angle != 0)
        {
            // Since SDL doesn't rotate "from the center", we must send it
            // the difference between the center points of both.
            tmpRect.x += ((this->clipRect->w)/2 - (this->surfaceRotoZoom->w)/2);
            tmpRect.y += ((this->clipRect->h)/2 - (this->surfaceRotoZoom->h)/2);
        }

        //SDL::renderSurface(this->surfaceRotoZoom, this->rotoZoomClipRect, &tmpRect);
        SDL::renderSurface(this->surfaceRotoZoom, NULL, &tmpRect);
    }
    else
        SDL::renderSurface(this->surface, this->clipRect, &tmpRect);
}
void Sprite::setTransparentRGBColor(Color color)
{
    Uint32 colorKey = SDL_MapRGB(this->surface->format,
                                 color.r(), color.g(), color.b());

    SDL_SetColorKey(this->surface, SDL_SRCCOLORKEY, colorKey);
}
int Sprite::getWidth()
{
    if (this->surfaceRotoZoom)
        return (this->rotoZoomClipRect.w);

    else
        return (this->clipRect->w);
}
int Sprite::getHeight()
{
    if (this->surfaceRotoZoom)
        return (this->rotoZoomClipRect.h);

    else
        return (this->clipRect->h);
}
void Sprite::update(uint32_t dt)
{
    // Yep. Nothing
    UNUSED(dt);
}
void Sprite::rotoZoom(float angle, float scaleX, float scaleY, bool force)
{
    if (force == false)
    {
        if ((this->angle  == angle)  &&
            (this->scaleX == scaleX) &&
            (this->scaleY == scaleY))
            return;
    }
    this->restore();

    this->angle  = angle;
    this->scaleX = scaleX;
    this->scaleY = scaleY;

    SDL_Rect tmp;
    tmp.x = this->clipRect->x;
    tmp.y = this->clipRect->y;
    tmp.w = this->clipRect->w;
    tmp.h = this->clipRect->h;

    SDL_Surface* tmpSurface;
    tmpSurface = SDL::clip(this->surface, &tmp);

    this->surfaceRotoZoom = SDL::rotoZoom(tmpSurface, this->angle, this->scaleX, this->scaleY);

    SDL_FreeSurface(tmpSurface);

    this->rotoZoomClipRect.x = 0;
    this->rotoZoomClipRect.y = 0;
    this->rotoZoomClipRect.w = this->surfaceRotoZoom->w;
    this->rotoZoomClipRect.h = this->surfaceRotoZoom->h;

//   this->clipRect->w = this->surfaceRotoZoom->w;
//   this->clipRect->h = this->surfaceRotoZoom->h;
}
void Sprite::restore()
{
    if (this->surfaceRotoZoom)
    {
        SDL_FreeSurface(this->surfaceRotoZoom);
        this->surfaceRotoZoom = NULL;
    }
}
SDL_Rect* Sprite::getClip()
{
    if (this->surfaceRotoZoom)
        return &(this->rotoZoomClipRect);
    else
        return (this->clipRect);
}
void Sprite::clip(int x, int y, int w, int h)
{
    this->clipRect->x = x;
    this->clipRect->y = y;
    this->clipRect->w = w;
    this->clipRect->h = h;

    if (this->surfaceRotoZoom)
        this->rotoZoom(this->angle, this->scaleX, this->scaleY, true);
}

