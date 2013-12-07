#include "GameStateGame.hpp"
#include "StateManager.hpp"
#include "Config.hpp"
#include "Log.hpp"
#include "Window.hpp"
#include "LoadingScreen.hpp"

bool GameStateGame::showBoundingBoxes = false;

GameStateGame::GameStateGame():
    bg(NULL),
    planetSprite(NULL),
    earthSprite(NULL),
    moonSprite(NULL),
    ufoSprite(NULL),
    shipAnim(NULL),
    explosionAnim(NULL),
    earth(NULL),
    moon(NULL),
    will_quit(false),
    game_over(false),
    tileSet(NULL),
    tileMap(NULL),
    camera(NULL),
    ufo(NULL),
    bgmusic(NULL),
    ship(NULL),
    explosion(NULL),
    lifeBar(NULL),
    lifeBarFont(NULL),
    lifeBarText(NULL),
    isPaused(false),
    font(NULL),
    pausedTitle(NULL)
{ }
GameStateGame::~GameStateGame()
{ }
void GameStateGame::load(int stack)
{
    UNUSED(stack);

    LoadingScreen loading("loading...", "ttf/Terminus.ttf");

    this->bg = new Sprite("img/game-bg.png");

    loading.increase(2);

    this->planetSprite = new Sprite("img/PlanetaVermelho.png");

    loading.increase(3);

    loading.increase(4);

    this->earthSprite = new Sprite("img/PlanetaTerra.png");
    this->earthSprite->rotoZoom(0, 2.0, 2.0);
    this->earth = new Earth(this->earthSprite, 20,
                            SDL::randomNumberBetween(-1000, 1000),
                            SDL::randomNumberBetween(-1000, 1000),
                            this->earthSprite->getWidth(),
                            this->earthSprite->getHeight());

    loading.increase(8);

    this->moonSprite = new Sprite("img/Lua.png");
    this->moon       = new Moon(this->moonSprite, 1, this->earth,
                                this->moonSprite->getWidth(),
                                this->moonSprite->getHeight());

    loading.increase(8);

    this->tileSet = new TileSet("img/Tileset.png", 6, 6);
    this->tileMap = new TileMap("map/map.tmx", this->tileSet);

    loading.increase(12);

    this->camera = new Camera(0, 0, Window::width,
                              Window::height,
                              Config::cameraScrollSpeed);

    loading.increase(3);

    this->ufoSprite = new Sprite("img/ufo.png");
    this->ufo = new FollowerObject(this->ufoSprite, 30, 30,
                                   this->ufoSprite->getWidth(),
                                   this->ufoSprite->getHeight(), 20);

    loading.increase(8);

    this->shipAnim = new Animation("img/NaveSheet.png", 4, 18);
    this->ship = new AccellObject(this->shipAnim,
                                  Window::width/2, Window::height/2,
                                  94, 100, 20);

    // Camera must be centered on the ship at ALL times
    this->camera->centerOn(this->ship->getX() + this->ship->getWidth()/2,
                           this->ship->getY() + this->ship->getHeight()/2);

    loading.increase(10);

    this->explosionAnim = new Animation("img/explosion.png", 22, 30);
    this->explosion = new Explosion(this->explosionAnim);

    loading.increase(8);

    this->lifeBar = new ProgressBar(200, 20, this->ship->getHitpoints(), this->ship->getHitpoints());
    this->lifeBar->setForegroundColor(Color(255, 0, 255));
    this->lifeBar->setBackgroundColor(Color(100, 0, 100));

    loading.increase(4);

    this->lifeBarFont = new Font("ttf/UbuntuMono.ttf", 16);
    this->lifeBarText = new Text(this->lifeBarFont);
    this->lifeBarText->setText("Energy");
    this->lifeBarText->setPosition(10, 10);

    loading.increase(4);

    this->font = new Font("ttf/UbuntuMono.ttf", 42);

    loading.increase(5);

    this->pausedTitle = new Text(this->font);
    this->pausedTitle->setText("Paused");
    this->pausedTitle->setPosition((Window::width/2) - 50,
                                   (Window::height/2) - 100);

    loading.increase(5);

    this->hiliteFont = new Font("ttf/UbuntuMono.ttf", 42);
    this->hiliteFont->setColor(Color(100, 100, 100));

    loading.increase(5);

    this->pausedMenu = new Menu(this->font, this->hiliteFont,
                                Window::width/2  - 60,
                                Window::height/2 + 100);

    this->pausedMenu->addItem("Continue");
    this->pausedMenu->addItem("Exit");
    this->pausedMenu->centralizeText();

    loading.increase(13);

    this->bgmusic = new Music("ogg/escaping.ogg");
    this->bgmusic->play();

    loading.increase(10);
}
int GameStateGame::unload()
{
    // Before deleting everything, we must see if we
    // just won.
    // If we did, then this->ufo will be NULL
    bool we_won = false;

    if (!(this->ufo))
        we_won = true;

// Time to delete!
// This macro deletes a thing only if it's non-NULL,
// making sure it won't double-delete things.
#define safe_delete(x) \
{                      \
    if (x)             \
    {                  \
        delete (x);    \
        x = NULL;      \
    }                  \
}

    int size = this->planetArray.size();

    for (int i = 0; i < size; i++)
        safe_delete(this->planetArray[i]);

    safe_delete(this->planetSprite);

    safe_delete(this->bg);
    safe_delete(this->bgmusic);
    safe_delete(this->camera);

    safe_delete(this->tileSet);
    safe_delete(this->tileMap);

    safe_delete(this->earth);
    safe_delete(this->earthSprite);

    safe_delete(this->moon);
    safe_delete(this->moonSprite);

    safe_delete(this->ship);
    safe_delete(this->shipAnim);

// TODO there's a segmentation fault when I delete explosion
//      why is that?
//    safe_delete(this->explosion);

    safe_delete(this->explosionAnim);

    safe_delete(this->font);
    safe_delete(this->pausedTitle);
    safe_delete(this->hiliteFont);
    safe_delete(this->pausedMenu);

    safe_delete(this->lifeBar);
    safe_delete(this->lifeBarFont);
    safe_delete(this->lifeBarText);

    if (we_won)
        return 1;
    else
        return 0;
}
int GameStateGame::update(uint32_t dt)
{
    if (this->will_quit)
        return GameState::QUIT;

    // Player/UFO has died.
    // Will only go to the GAME OVER screen when the
    // explosion ends.
    if (this->game_over)
        if (!(this->explosion->isExploding()))
            return GameState::GAME_OVER;

    this->processEvents();

    if (this->isPaused)
    {
        this->pausedMenu->update();
        return GameState::CONTINUE;
    }

    int size = this->planetArray.size();
    for (int i = 0; i < size; i++)
        this->planetArray[i]->update(dt);

    this->earth->update(dt);
    this->moon->update(dt);

    if (this->ufo)
        this->ufo->update(dt);

    if (this->ship)
        this->ship->update(dt);

    this->camera->update(dt);

    if (this->ship)
        this->camera->centerOn(this->ship->getX() + this->ship->getWidth()/2,
                               this->ship->getY() + this->ship->getHeight()/2);

    this->checkCollision();
    this->explosion->update(dt);

    return GameState::CONTINUE;
}
void GameStateGame::render()
{
    int cameraX = this->camera->getX();
    int cameraY = this->camera->getY();

    this->bg->render(0, 0);

    for (int i = 0; i < (this->tileMap->getLayers()); i++)
        this->tileMap->renderLayer(cameraX, cameraY, i);

//    this->tileMap->render(cameraX, cameraY, true);

    int size = this->planetArray.size();
    for (int i = 0; i < size; i++)
        this->planetArray[i]->render(cameraX, cameraY);

    this->earth->render(cameraX, cameraY);
    this->moon->render(cameraX, cameraY);

    if (this->ufo)
	    if (!(this->ufo->isDead()))
		    this->ufo->render(cameraX, cameraY);

    if (!(this->ship->isDead()))
        this->ship->render(cameraX, cameraY);

    this->explosion->render(cameraX, cameraY);

    this->lifeBar->render(10, 10);
    this->lifeBarText->render();

    if (this->isPaused)
    {
        this->pausedTitle->render();
        this->pausedMenu->render();
    }
}
void GameStateGame::checkCollision()
{
    if (!(this->ufo) || !(this->ship))
        return;

    this->checkPlanets();

    if (this->ship->collidedWith(this->earth))
    {
        this->ufo->damage(666);
        this->game_over = true;
    }

    if (this->ship->isDead())
    {
        this->explosion->explodeAt(this->ship->getX(),
                                   this->ship->getY());
        delete this->ship;
        this->ship = NULL;

        this->game_over = true;
    }
    if (this->ufo->isDead())
    {
        this->explosion->explodeAt(this->ufo->getX(),
                                   this->ufo->getY());
        delete this->ufo;
        this->ufo = NULL;
    }
}
void GameStateGame::addPlanet()
{
    int hit = SDL::randomNumberBetween(1, 20);
    int x   = SDL::randomNumberBetween(0, Window::width  - 1);
    int y   = SDL::randomNumberBetween(0, Window::height - 1);

    PlanetRed* planet = new PlanetRed((this->planetSprite),
                                      hit,
                                      x + this->camera->getX(),
                                      y + this->camera->getY(),
                                      this->planetSprite->getWidth(),
                                      this->planetSprite->getHeight());

    this->planetArray.push_back(planet);
    Log::debug("GameStateGame::addPlanet Successful");
}
void GameStateGame::checkPlanets()
{
    int size = this->planetArray.size();

    for (int i = 0; i < size; i++)
    {
        if (this->ship->collidedWith(this->planetArray[i]))
        {
            this->explosion->explodeAt(this->planetArray[i]->getX(),
                                       this->planetArray[i]->getY());
            this->planetArray[i]->damage(666);
            this->ship->damage(1);
            this->lifeBar->decrease(1);
        }

        if (this->planetArray[i]->isDead())
        {
            delete this->planetArray[i];
            this->planetArray.erase(this->planetArray.begin() + i);
            Log::debug("GameStateGame::checkPlanets Delete Planet no " +
                       SDL::intToString(i));
        }
    }
}
void GameStateGame::processEvents()
{
    InputManager* input = InputManager::getInstance();
    input->update(this->camera->getX(), this->camera->getY());

    this->will_quit = input->quitRequested();

    if ((input->isKeyDown(SDLK_ESCAPE)) ||
        (input->isKeyDown(SDLK_q)))
        this->will_quit = true;

    if (input->isKeyDown(SDLK_p))
        this->isPaused?
            this->isPaused = false:
            this->isPaused = true;

    // The only things we're going to care when the game is
    // paused are quitting, unpausing and the pause menu.
    if (this->isPaused)
    {
        if ((input->isKeyPressed(SDLK_RETURN)) ||
            (this->pausedMenu->mouseClickedOnItem()))
        {
            switch (this->pausedMenu->getCurrentItemIndex())
            {
            case 0:
                this->isPaused = false;
                break;
            case 1:
                this->will_quit = true;
                break;
            default:
                break;
            }
        }
        return;
    }

    if ((input->isKeyDown(SDLK_F2)))
        this->game_over = true;

    // Unused keys - previously they scrolled the
    //               camera, but now it's focused
    //               on the player
    if (input->isKeyDown(SDLK_UP))
        this->camera->scroll(Camera::UP);

    if (input->isKeyDown(SDLK_DOWN))
        this->camera->scroll(Camera::DOWN);

    if (input->isKeyDown(SDLK_LEFT))
        this->camera->scroll(Camera::LEFT);

    if (input->isKeyDown(SDLK_RIGHT))
        this->camera->scroll(Camera::RIGHT);

    if (input->isKeyUp(SDLK_UP))
        this->camera->unscroll(Camera::UP);

    if (input->isKeyUp(SDLK_DOWN))
        this->camera->unscroll(Camera::DOWN);

    if (input->isKeyUp(SDLK_LEFT))
        this->camera->unscroll(Camera::LEFT);

    if (input->isKeyUp(SDLK_RIGHT))
        this->camera->unscroll(Camera::RIGHT);
    // End of unused keys

    if (input->isKeyDown(SDLK_f))
        Window::toggleFullscreen();

    // These are extra keys that I've added for teh lulz

    // Toggle bounding boxes
    if (input->isKeyDown(SDLK_F1))
        (GameStateGame::showBoundingBoxes)?
            GameStateGame::showBoundingBoxes = false:
            GameStateGame::showBoundingBoxes = true;

    // Reloading config file at runtime!
    if (input->isKeyDown(SDLK_r))
        Config::reload();

    // Reloading map file at runtime!
    if (input->isKeyDown(SDLK_m))
        this->tileMap->reload();

    if (input->isMouseDown(SDL_BUTTON_LEFT))
        this->addPlanet();

    // Empty ufo command list
    if (input->isMouseDown(SDL_BUTTON_MIDDLE))
    {
        if (this->ufo)
            this->ufo->empty();
    }

    if (input->isMouseDown(SDL_BUTTON_RIGHT))
    {
        if (this->ufo)
            this->ufo->enqueueCommand(input->getMouseX(),
                                      input->getMouseY());
    }

    if (input->isKeyDown(SDLK_F3))
        Window::center();

    if (input->isKeyDown(SDLK_F4))
        Window::setPosition(10, 10);
}

