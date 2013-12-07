#include "InputManager.hpp"
#include "Window.hpp"

InputManager* InputManager::instance = NULL;

InputManager::InputManager():
    keyboard(NULL),
    mouseX(0),
    mouseY(0),
    will_quit(false)
{ }

// TODO find out why I didn't pick this one
// InputManager& InputManager::getInstance()
// {
//     static InputManager instance;
//     return instance;
// }

InputManager* InputManager::getInstance()
{
    if (!instance)
        instance = new InputManager();

    return instance;
}
void InputManager::update(float cameraX, float cameraY)
{
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
    {
        this->keyDown[i] = false;
        this->keyUp[i]   = false;
    }
    for (i = 0; i < MOUSE_SIZE; i++)
    {
        this->mouseDown[i] = false;
        this->mouseUp[i]   = false;
    }

    // get key events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->will_quit = true;
            break;

        case SDL_KEYDOWN:
            this->keyboard = SDL_GetKeyState(NULL);
            this->keyDown[event.key.keysym.sym] = true;
            break;

        case SDL_KEYUP:
            this->keyboard = SDL_GetKeyState(NULL);
            this->keyUp[event.key.keysym.sym] = true;
            break;

        case SDL_MOUSEMOTION:
            this->mouse = SDL_GetMouseState(&(this->mouseX), &(this->mouseY));
            this->mouseX += cameraX;
            this->mouseY += cameraY;
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            this->mouse = SDL_GetMouseState(&(this->mouseX), &(this->mouseY));
            this->mouseX += cameraX;
            this->mouseY += cameraY;
            if (event.button.state == SDL_PRESSED)
                this->mouseDown[event.button.button] = true;
            else
                this->mouseUp[event.button.button] = true;
            break;

            // This is a special interface to the window, making
            // it able to resize.
            // It shouldn't be on the input manager (modularity)
            // but what the heck.
        case SDL_VIDEORESIZE:
            Window::resize(event.resize.w, event.resize.h);
            break;

        case SDL_ACTIVEEVENT:
            // If the window was minimized or restored
            if (event.active.state & SDL_APPACTIVE)
            {
                // If the window was minimized
                if (event.active.gain == 0)
                {
                    // DO SOMETHING
                }
                // If the window was restored
                else
                {
                    // DO SOMETHING
                }
            }
            // If something happened to the keyboard focus (Alt+Tab)
            else if (event.active.state & SDL_APPINPUTFOCUS)
            {
                // If we lost the keyboard focus
                if (event.active.gain == 0)
                {
                    // DO SOMETHING
                }
                // If we restored the keyboard focus
                else
                {
                    // DO SOMETHING
                }
            }
            // If something happened to the mouse
            else if (event.active.state & SDL_APPMOUSEFOCUS)
            {
                // If we lost the mouse focus
                if (event.active.gain == 0)
                {
                    // DO SOMETHING
                }
                // If we recovered mouse focus
                {
                    // DO SOMETHING
                }
            }
            break;

        case SDL_VIDEOEXPOSE:
            // Something outside the program altered the screen.
            // I don't really know what it means, so let's just
            // refresh the screen.
            Window::refresh();
            break;

        default:
            break;
        }
    }
}
bool InputManager::isKeyDown(int key)
{
    if (key < SDLK_FIRST || key > SDLK_LAST)
        return false;

    return (this->keyDown[key]);
}
bool InputManager::isKeyUp(int key)
{
    if (key < SDLK_FIRST || key > SDLK_LAST)
        return false;

    return (this->keyUp[key]);
}
bool InputManager::isMouseDown(uint8_t button)
{
    if (button > 3)
        return false;

    return this->mouseDown[button];
}
bool InputManager::isMouseUp(uint8_t button)
{
    if (button > 3)
        return false;

    return this->mouseUp[button];
}
bool InputManager::isKeyPressed(int key)
{
    if (key < SDLK_FIRST || key > SDLK_LAST)
        return false;

    if (!(this->keyboard))
        return false;

    if (this->keyboard[key])
        return true;

    return false;
}
bool InputManager::isMousePressed(uint8_t button)
{
    if (button < 1 || button > 3)
        return false;

    // yes, it's a bitwise operation
    if (this->mouse & SDL_BUTTON(button))
        return true;

    return false;
}
int InputManager::getMouseX()
{
    return this->mouseX;
}
int InputManager::getMouseY()
{
    return this->mouseY;
}
bool InputManager::quitRequested()
{
    bool alt_f4 = false;
    if (instance->isKeyDown(SDLK_F4) &&
        ((instance->isKeyPressed(SDLK_RALT)) ||
         (instance->isKeyPressed(SDLK_LALT))))
        alt_f4 = true;

    return ((this->will_quit) || (alt_f4));
}
bool InputManager::isMouseInside(int x, int y, int w, int h)
{
    if ((this->mouseX >= x) && (this->mouseX <= x + w) &&
        (this->mouseY >= y) && (this->mouseY <= y + h))
        return true;

    return false;
}

