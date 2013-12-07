#include "Menu.hpp"
#include "InputManager.hpp"
#include "Graphics.hpp"

Menu::Menu(Font* font, Font* hiliteFont, float x, float y):
    font(font),
    hiliteFont(hiliteFont),
    item(),
    items(0),
    currentItem(0),
    x(x),
    y(y),
    width(0),
    height(0),
    mouseSelectedItem(false)
{ }
Menu::~Menu()
{
    for (int i = 0; i < (this->items); i++)
        if (this->item[i])
            delete this->item[i];
}
void Menu::addItem(std::string text, int value)
{
    if (!(this->font)) return;

    Text* tmpText = new Text(this->font);
    tmpText->setText(text);
    tmpText->setPosition((this->x),
                         (this->items * tmpText->getHeight()) + this->y + 5);

    MenuItem* tmpItem = new MenuItem(tmpText, value);

    this->item.push_back(tmpItem);
    this->items++;

    if ((tmpItem->text->getWidth()) > (this->width))
        this->width = tmpItem->text->getWidth();

    this->height += (tmpItem->text->getHeight());

    if (this->items == 1)
        this->item[0]->text->setFont(this->hiliteFont);
}
int Menu::getCurrentItemValue()
{
    return (this->item[currentItem]->value);
}
int Menu::getCurrentItemIndex()
{
    return (this->currentItem);
}
int Menu::getAmmount()
{
    return (this->items);
}
void Menu::next()
{
    if (this->currentItem >= (this->items - 1))
    {
        this->first(); // I could simply block the item
        return;        // from going, but it's nice to
    }                  // wrap up the menu.

    this->item[currentItem]->text->setFont(this->font);
    this->currentItem++;
    this->item[currentItem]->text->setFont(this->hiliteFont);
}
void Menu::previous()
{
    if (this->currentItem <= 0)
    {
        this->last();
        return;
    }
    this->item[currentItem]->text->setFont(this->font);
    this->currentItem--;
    this->item[currentItem]->text->setFont(this->hiliteFont);
}
void Menu::first()
{
    this->item[currentItem]->text->setFont(this->font);
    this->currentItem = 0;
    this->item[currentItem]->text->setFont(this->hiliteFont);
}
void Menu::last()
{
    this->item[currentItem]->text->setFont(this->font);
    this->currentItem = (items - 1); // counts from zero
    this->item[currentItem]->text->setFont(this->hiliteFont);
}
void Menu::render(float cameraX, float cameraY)
{
    // print borders for debuggin purposes
    // {
    //     Graphics::drawRectangle(this->x,
    //                             this->y,
    //                             this->width,
    //                             this->height);
    // }

    for (int i = 0; i < (this->items); i++)
        this->item[i]->text->render(cameraX, cameraY);
}
void Menu::update(uint32_t dt)
{
    UNUSED(dt);

    this->mouseSelectedItem = false;

    InputManager* input = InputManager::getInstance();

    if (input->isKeyDown(SDLK_UP))
        this->previous();

    if (input->isKeyDown(SDLK_DOWN))
        this->next();

    if (input->isKeyDown(SDLK_PAGEUP))
        this->first();

    if (input->isKeyDown(SDLK_PAGEDOWN))
        this->last();

    if (input->isMouseInside(this->x, this->y, this->width, this->height))
    {
        for (int i = 0; i < (this->items); i++)
        {
            Text* text = this->item[i]->text;

            if (input->isMouseInside(text->getX(),     text->getY(),
                                     text->getWidth(), text->getHeight()))
            {
                this->item[currentItem]->text->setFont(this->font);
                this->currentItem = i;
                this->item[currentItem]->text->setFont(this->hiliteFont);

                if (input->isMousePressed(SDL_BUTTON_LEFT))
                    this->mouseSelectedItem = true;
            }
        }
    }
}
void Menu::centralizeText()
{
    // tell everyone to centralize and move the text
    // so it can be right on the middle of the menu.

    for (int i = 0; i < (this->items); i++)
    {
        Text* tmp = this->item[i]->text;
        tmp->setAlignment(Text::CENTER);

        tmp->setPosition(tmp->getX() + (this->width/2),
                         tmp->getY());
    }
}
bool Menu::mouseClickedOnItem()
{
    return (this->mouseSelectedItem);
}

