#ifndef PROGRESSBAR_H_DEFINED
#define PROGRESSBAR_H_DEFINED

#include "SDL.hpp"
#include "Color.hpp"

/// Defines a general-purpose progress bar.
///
class ProgressBar
{
public:
    /// Creates a progress bar with *width* and *height* (both
    /// in pixels as how will be shown onscreen), and *max* and
    /// *starting* values of the progress.
    ///
    /// It grows from the left to the right.
    ProgressBar(int width, int height, int max=100, int starting=0);
    virtual ~ProgressBar();

    /// Increases progress by *ammount*.
    void increase(int ammount);

    /// Decreases progress by *ammount*.
    void decrease(int ammount);

    /// Tells if the progress bar is currently full.
    bool isFull();

    /// Tells if the progress bar is still at 0%.
    bool isEmpty();

    void setBackgroundColor(Color color=Color(0, 0, 0));
    void setForegroundColor(Color color=Color(255, 255, 255));

    /// Shows progress bar on *x* and *y* positions of the screen.
    void render(int x, int y);

private:
    int maxValue;
    int currentValue;
    int width;
    int height;
    bool isComplete;
    bool isZero;

    SDL_Surface* surface;

    Color filledColor;
    Color emptyColor;
};

#endif //PROGRESSBAR_H_DEFINED

