#include "TileSet.hpp"

TileSet::TileSet(std::string filePath, int lines, int columns)
{
    this->singleFile = true;
    this->tileSet    = new Sprite(filePath);
    this->columns    = columns;
    this->lines      = lines;
    this->tileWidth  = this->tileSet->getWidth()  / columns;
    this->tileHeight = this->tileSet->getHeight() / lines;
}
TileSet::TileSet(int tileWidth, int tileHeight, std::string filePath)
{
    this->singleFile  = true;
    this->tileWidth   = tileWidth;
    this->tileHeight  = tileHeight;
    this->tileSet     = new Sprite(filePath);
    this->columns     = this->tileSet->getWidth()  / tileWidth;
    this->lines       = this->tileSet->getHeight() / tileHeight;
}
TileSet::TileSet(int tileWidth, int tileHeight)
{
    this->singleFile = false;
    this->lines      = 0;
    this->columns    = 0;
    this->tileWidth  = tileWidth;
    this->tileHeight = tileHeight;
    this->tileSet    = NULL;
}
TileSet::~TileSet()
{
    if (this->tileSet) delete this->tileSet;
}
void TileSet::addTile(std::string filePath)
{
    if (this->singleFile) return;

    Sprite* sprite = new Sprite(filePath);
    this->vTiles.push_back(sprite);
}
void TileSet::render(int index, float posX, float posY)
{
    if (this->singleFile)
    {
        // We'll calculate where is the current tile on the big
        // image based on its #index.
        // For example:
        //
        //          columns
        //        0  1  2  3
        //      +------------+
        // l  0 | 1  2  3  4 |
        // i  1 | 5  6  7  8 |
        // n  2 | 9 10 11 12----> index
        // e  3 |13 14 15 16 |
        // s  4 |17 18 19 20 |
        //      +------------+

        int x = (index) % (this->columns);
        int y = (index) / (this->lines);
        int w = this->tileWidth;
        int h = this->tileHeight;

        // Crops the big image on the position of the tile
        this->tileSet->crop((x * w), (y * h), w, h);
        this->tileSet->render(posX, posY);
    }
    else
        this->vTiles[index]->render(posX, posY);
}
bool TileSet::usingSingleFile()
{
    return this->singleFile;
}
int TileSet::getTileWidth()
{
    return this->tileWidth;
}
int TileSet::getTileHeight()
{
    return this->tileHeight;
}

