#include "LoadingScreen.hpp"
#include "Window.hpp"

LoadingScreen::LoadingScreen(std::string text, std::string fontPath):
    font(fontPath, 56),
    text(&(this->font)),
    progressBar(400, 20, 100, 0)
{
    this->text.setText(text);
    this->text.setPosition(270, 300);

    this->progressBar.setBackgroundColor(Color(10, 95, 10));
    this->progressBar.setForegroundColor(Color(20, 255, 20));

    Window::clear();
    this->text.render();

    // rendering progress bar for the first time
    this->increase(0);
}

void LoadingScreen::increase(int ammount)
{
    this->progressBar.increase(ammount);
    this->progressBar.render(200, 500);
    Window::refresh();
}


