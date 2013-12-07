#include "GameStateMainMenu.hpp"
#include "InputManager.hpp"
#include "SDL.hpp"
#include "Window.hpp"
#include "LoadingScreen.hpp"

GameStateMainMenu::GameStateMainMenu():
    font(NULL),
    music(NULL),
    menu(NULL),
    bg(NULL)
{ }
GameStateMainMenu::~GameStateMainMenu()
{ }
void GameStateMainMenu::load(int stack)
{
    UNUSED(stack);

    LoadingScreen loading("Loading...", "ttf/UbuntuMono.ttf");

    this->font = new Font("ttf/UbuntuMono.ttf", 42);
    this->hiliteFont = new Font("ttf/Terminus.ttf", 42);

    loading.increase(12);

    this->font->setColor(Color(0, 0, 0));
    this->hiliteFont->setColor(Color(100, 100, 100));

    loading.increase(12);

    this->music = new Music("ogg/saturno.ogg");
    music->play();

    loading.increase(4);

    this->menu = new Menu(this->font, this->hiliteFont, 600, 200);
    this->menu->addItem("New Game");
    this->menu->addItem("Credits");
    this->menu->addItem("Exit");
    this->menu->centralizeText();

    loading.increase(6);

    this->bg = new Sprite("img/menu-bg.png");

    loading.increase(10);
}
int GameStateMainMenu::unload()
{
    if (this->font)
        delete this->font;

    if (this->hiliteFont)
        delete this->hiliteFont;

    if (this->music)
    {
        this->music->stop();
        delete this->music;
    }

    if (this->menu)
        delete this->menu;

    if (this->bg)
        delete this->bg;

    return 0;
}
int GameStateMainMenu::update(uint32_t dt)
{
    UNUSED(dt);

    InputManager* input = InputManager::getInstance();
    input->update();

    this->menu->update();

    if ((input->isKeyDown(SDLK_ESCAPE)) ||
        (input->isKeyPressed(SDLK_q))   ||
        (input->quitRequested()))
        return GameState::QUIT;

    // interacting with the menu
    if ((input->isKeyPressed(SDLK_RETURN)) ||
        (menu->mouseClickedOnItem()))
    {
        switch (this->menu->getCurrentItemIndex())
        {
        case 0:
            return GameState::GAME_START;
            break;
        case 1:
            break;
        case 2:
            return GameState::QUIT;
            break;
        default:
            break;
        }
    }

    return GameState::CONTINUE;
}
void GameStateMainMenu::render()
{
    // this->font->print(30, 30, "Main Menu");

    // this->font->print(100, 300, "IT WORKS!");

    // this->font->print(400, 400,
    //                   "Aperte 'up' pra iniciar,"
    //                   "'q' para sair.");
    this->bg->render(0, 0);
    this->menu->render();
}

