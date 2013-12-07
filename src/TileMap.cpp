#include "TileMap.hpp"
#include "lib/TmxParser/Tmx.h"
#include "Log.hpp"

// Just easing writing of stuff
#define vect std::vector

TileMap::TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet)
{
    this->mapWidth  = mapWidth;
    this->mapHeight = mapHeight;
    this->mapLayers = layers;
    this->tileSet   = tileSet;
    this->loaded    = true;

    unsigned int i, j;

    // 1st dimension
    this->tileMatrix.resize(mapWidth);

    // 2nd dimension
    for (i = 0; i < (this->tileMatrix.size()); i++)
        this->tileMatrix[i].resize(mapHeight);

    // 3rd dimension
    for (i = 0; i < (this->tileMatrix.size()); i++)
        for (j = 0; j < (this->tileMatrix[0].size()); j++)
            this->tileMatrix[i][j].resize(layers, -1);
}
TileMap::TileMap(std::string mapa, TileSet* tileSet)
{
    this->tileSet = tileSet;
    this->loaded  = this->load(mapa);
}
bool TileMap::load(std::string mapPath)
{
    this->mapFile = mapPath;

    // The Tmx parser's data structure
    Tmx::Map map;

    map.ParseFile(mapPath);
    if (map.HasError())
    {
        Log::error("map.ParseFile: Couldn't parse Map file '" +
                   mapPath + "': " +
                   std::string(map.GetErrorText()));
        return false;
    }

    // All layers MUST be of the same width and height!
    int layers      = map.GetNumLayers();
    this->mapLayers = layers;

    const Tmx::Layer* currentLayer = map.GetLayer(0);
    int mapWidth  = currentLayer->GetWidth();
    int mapHeight = currentLayer->GetHeight();

    unsigned int i, j, k;

    // Now I'll set the size of the tileMatrix, starting all the
    // tiles with default value of 0
    // 1st dimension
    this->tileMatrix.resize(mapWidth);

    // 2nd dimension
    for (i = 0; i < (this->tileMatrix.size()); i++)
        this->tileMatrix[i].resize(mapHeight);

    // 3rd dimension
    for (i = 0; i < (this->tileMatrix.size()); i++)
        for (j = 0; j < (this->tileMatrix[0].size()); j++)
            this->tileMatrix[i][j].resize(layers, 0);

    for (i = 0; i < (unsigned int)layers; i++)
    {
        currentLayer = map.GetLayer(i);

        // Saving all the tile ids on the tile Matrix
        for (j = 0; j < (unsigned int)mapWidth; j++)
	        for (k = 0; k < (unsigned int)mapHeight; k++)
                this->tileMatrix[j][k][i] = currentLayer->GetTileId(j, k);
    }

    Log::debug("TileMap::load Map loaded (width:" +
               SDL::intToString(mapWidth)  +
               " height:" +
               SDL::intToString(mapHeight) +
               " layers:" +
               SDL::intToString(layers) +
               ")");
    return true;
}
bool TileMap::reload()
{
    return this->load(this->mapFile);
}
void TileMap::setTileset(TileSet* tileSet)
{
    this->tileSet = tileSet;
}
int& TileMap::at(int x, int y, int z)
{
    return this->tileMatrix[x][y][z];
}
void TileMap::render(float cameraX, float cameraY, bool parallax)
{
    if (!(this->loaded))  return;
    if (!(this->tileSet)) return;

    int x = this->tileMatrix.size();
    int y = this->tileMatrix[0].size();
    int z = this->tileMatrix[0][0].size();
    int w = this->tileSet->getTileWidth();
    int h = this->tileSet->getTileHeight();

    // Parallax constant
    // (bigger values will move layers faster)
    float parall = 0.3;

                                        // For each and every tile...
    for (int i = 0; i < x; i++)         // ...on position X
        for (int j = 0; j < y; j++)     // ...and position Y
            for (int k = 0; k < z; k++) // ...on layer K
            {
                int index = tileMatrix[i][j][k]; // ...get his index...
                if (index > 0)                   // ...and if it's valid,
                {                                // print onscreen!
//                    int posX = (i * w) - cameraX;
//                    int posY = (j * h) - cameraY;

                    // Ammount of parallax to actually move the screen
                    // (on pixels)
                    float parallAdd = parallax? (parall * (k+1)) : 1;

                    // Where on the screen we will print the tile?
                    float posX = (i * w) - (cameraX * parallAdd);
                    float posY = (j * h) - (cameraY * parallAdd);

                    this->tileSet->render(index, posX, posY);
                }
            }
}
void TileMap::renderLayer(float cameraX, float cameraY, int layer)
{
    if (!(this->loaded))  return;
    if (!(this->tileSet)) return;

    // Invalid layer number!
    if ((unsigned int)layer > (this->tileMatrix[0][0].size()))
	    return;

    int x = this->tileMatrix.size();
    int y = this->tileMatrix[0].size();
    int w = this->tileSet->getTileWidth();
    int h = this->tileSet->getTileHeight();

    float parallax = 0.3;

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            int index = tileMatrix[i][j][layer];
            if (index > 0)      // if it is a valid tile
            {
                float parallAdd = (parallax * (layer+1));
                float posX = ((i * w) - cameraX * parallAdd);
                float posY = ((j * h) - cameraY * parallAdd);
                this->tileSet->render(index, posX, posY);
            }
        }
}
int TileMap::getWidth()
{
    return this->mapWidth;
}
int TileMap::getHeight()
{
    return this->mapHeight;
}
int TileMap::getLayers()
{
    return this->mapLayers;
}

