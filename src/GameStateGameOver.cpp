#include "GameStateGameOver.hpp"
#include "InputManager.hpp"
#include "Window.hpp"

GameStateGameOver::GameStateGameOver():
    font(NULL),
    text1(NULL),
    text2(NULL),
    explosionAnim(NULL),
    explosion(NULL),
    music(NULL)
{ }
void GameStateGameOver::load(int stack)
{
    UNUSED(stack);

    this->font = new Font("ttf/UbuntuMono.ttf", 72);
    font->setColor(Color(255, 12, 12));

    this->text1 = new Text(this->font);
    this->text2 = new Text(this->font);

    if (stack == 0)
    {
        text1->setText("Game Over");
        text1->setPosition(250, 200);
    }
    else
    {
        text1->setText("Congratulations");
        text1->setPosition(150, 200);
    }

    text2->setText("Press 'r' to retry");
    text2->setPosition(60, 400);

    this->explosionAnim = new Animation("img/explosion.png", 22, 30);
    this->explosion = new Explosion(this->explosionAnim);

    this->music = new Music("ogg/cliffs.ogg");
    this->music->play();
}
int GameStateGameOver::unload()
{
    if (this->music) delete this->music;

// TODO there's a segmentation fault when I delete explosion
//      why is that?
//  if (this->explosion) delete this->explosion;

    if (this->explosionAnim) delete this->explosionAnim;
    return 0;
}
int GameStateGameOver::update(uint32_t dt)
{
	UNUSED(dt);

    InputManager* input = InputManager::getInstance();
    input->update();

    if ((input->isKeyDown(SDLK_r)) ||
        (input->isKeyDown(SDLK_RETURN)))
        return GameState::GAME_START;

    if ((input->isKeyDown(SDLK_q)) ||
        (input->isKeyDown(SDLK_ESCAPE)))
        return GameState::QUIT;

    if (input->quitRequested())
        return GameState::QUIT;

    // this->explosion->update(dt);
    // if (!(this->explosion->isExploding()))
    // {
    //     int x = SDL::randomNumberBetween(0, Window::width);
    //     int y = SDL::randomNumberBetween(0, Window::height);
    //     this->explosion->explodeAt(x, y);
    // }

    // if we're not doing anything it keeps TRAVANDO
    return GameState::CONTINUE;
}
void GameStateGameOver::render()
{
    text1->render();
    text2->render();
//    explosion->render();
}

