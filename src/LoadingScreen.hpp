#ifndef LOADINGSCREEN_H_DEFINED
#define LOADINGSCREEN_H_DEFINED

#include <string>
#include "Font.hpp"
#include "Text.hpp"
#include "ProgressBar.hpp"

/// General loading screen for the transition between states.
///
/// This is a temporary class. Generally must be used on the
/// *load()* methods of each state.
///
/// For a clear example, check out *GameStateGame*'s *load()*
/// method.
///
class LoadingScreen
{
public:
    /// Creates a loading screen with *text*, to be rendered
    /// by the font at *fontPath*.
    LoadingScreen(std::string text, std::string fontPath);

    /// Increase loading bar's percentage by *ammount*.
    void increase(int ammount);

private:
    Font font;
    Text text;
    ProgressBar progressBar;
};

#endif //LOADINGSCREEN_H_DEFINED

