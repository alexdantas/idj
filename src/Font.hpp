#ifndef FONT_H_DEFINED
#define FONT_H_DEFINED

#include "SDL.hpp"
#include <string>
//#include "Color.hpp"

class Color;

///
///
class Font
{
public:
    /// The font's type of renderization.
    //  Low-level printing options.
    enum RenderType { SOLID, BLENDED };

    /// Font's style.
    enum FontStyle { NORMAL, BOLD, ITALIC, UNDERLINE };

    /// Initializes pretty much everything.
    //  Yeah, don't bother calling any of the functions below unless
    //  you want to override the font or change it's size.
	Font(std::string filepath, int size, RenderType renderType=SOLID, Color color=Color(255, 255, 255));

	virtual ~Font();

    /// Loads the font into memory.
    //  This is automatically called when initialized, don't bother
    //  with it.
	bool load();

    /// Sets the current font to be the one on #filepath.
	void setFont(std::string filepath, int size=12);

    /// Sets the color of the font on RGB
    //  This is applied automatically, no need to call load().
	void setColor(Color color=Color(255, 0, 255));

    void setRenderType(RenderType renderType);

    /// Shows #text on positions #x and #y with #style.
    //  @note Keep in mind you must refresh screen after this.
    bool print(int x=0, int y=0, std::string text="abc", FontStyle style=NORMAL);

    /// Returns the font's width.
    int getWidth();

    /// Returns the font's height.
    int getHeight();

    SDL_Surface* render(std::string text);

    /// Returns the color as a SDL specific color-structure.
    SDL_Color getSDLColor();

private:
	std::string  filepath;
	TTF_Font*    font;
	int          size;
	Color        color;
	//SDL_Color    color;
	SDL_Surface* surface;
    RenderType   renderType;
};

#endif /* FONT_H_DEFINED */

