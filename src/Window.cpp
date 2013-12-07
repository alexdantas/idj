#include "Window.hpp"
#include "Log.hpp"

SDL_Surface* Window::screen           = NULL;
uint32_t     Window::width            = 0;
uint32_t     Window::height           = 0;
uint32_t     Window::flags            = 0;
bool         Window::isFullscreen     = false;
std::string  Window::caption          = "";
std::string  Window::minimizedCaption = "";
uint32_t     Window::bg_color         = 0;

bool Window::init(uint32_t width, uint32_t height, std::string windowCaption, std::string minimizedWindowCaption)
{
    Window::width  = width;
    Window::height = height;
    Window::caption = windowCaption;
    Window::minimizedCaption = minimizedWindowCaption;

    // SDL's internal flags
    Window::flags = (SDL_HWSURFACE | SDL_RESIZABLE);

    // Creates a RESIZABLE window! Store it on Window::screen.
    Window::resize(width, height);

    if (!(Window::screen))
    {
        Log::error("SDL_SetVideoMode: Couldn't set video mode");
        return false;
    }

    SDL_WM_SetCaption(Window::caption.c_str(),
                      Window::minimizedCaption.c_str());

    Window::setBackgroundColor();
    return true;
}
bool Window::toggleFullscreen()
{
    if (SDL_WM_ToggleFullScreen(Window::screen) == 0)
    {
        Log::warning("SDL_WM_ToggleFullScreen: "
                     "Couldn't toggle fullscreen mode");
        return false;
    }

    if (Window::isFullscreen == true)
        Window::isFullscreen = false;
    else
        Window::isFullscreen = true;

    return true;
}
bool Window::minimize()
{
    if (SDL_WM_IconifyWindow() == 0)
        return false;

    return true;
}
void Window::setIcon(std::string filepath)
{
    SDL_Surface* icon = SDL::loadImage(filepath, false);

    if (!icon)
    {
        Log::warning("SDL_WM_SetIcon: Couldn't load icon at '" +
                     filepath + "'");
        return;
    }

    SDL_WM_SetIcon(icon, NULL);
    SDL::freeImage(icon);
    Window::restart();
}
void Window::refresh()
{
    SDL_Flip(Window::screen);
}
void Window::clear()
{
    SDL_FillRect(Window::screen, NULL, bg_color);
}
void Window::setBackgroundColor(Color color)
{
    bg_color = SDL_MapRGB(Window::screen->format,
                          color.r(),
                          color.g(),
                          color.b());
}
void Window::resize(uint32_t width, uint32_t height)
{
    // Creates/updates the window, possibly storing it
    // on hardware memory and making it resizable.
    Window::screen = SDL_SetVideoMode(width, height, 0, Window::flags);
}
void Window::restart()
{
    Window::screen = SDL_SetVideoMode(Window::width,
                                      Window::height,
                                      0,
                                      Window::flags);
}
void Window::center()
{
    // I know this string conversion's ugly.
    // But I need to make a std::string into a char*
    // (NOT a const char*).
    //
    // For more info, see this:
    // http://stackoverflow.com/questions/347949/convert-stdstring-to-const-char-or-char/4152881#4152881

    std::string a = "SDL_VIDEO_CENTERED=center";
    char* c = &a[0];

    SDL_putenv(c);
    Window::restart();
}
void Window::setPosition(int x, int y)
{
    std::string a = "SDL_VIDEO_WINDOW_POS=" +
        SDL::intToString(x) +
        "," +
        SDL::intToString(y);

    char* c = &a[0];

    SDL_putenv(c);
    Window::restart();
}


