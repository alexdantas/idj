#ifndef TILESET_H_DEFINED
#define TILESET_H_DEFINED

#include <vector>
#include "SDL.hpp"
#include "Sprite.hpp"

/// Contains the group of all possible tiles.
//
//  To create a map from them, see class #TileMap
class TileSet
{
public:
    /// Starts TileSet with a single image, containing several tiles.
    //  @note Will parse automatically the image into single tiles
    //        based on #lines and #columns.
    TileSet(std::string filePath, int lines, int columns);

    /// Starts TileSet with a single image, containing several tiles.
    //  @note Will parse automatically the image into single tiles
    //        based on #tileWidth and #tileHeight.
    TileSet(int tileWidth, int tileHeight, std::string filePath);

    // Starts TileSet that will wait for multiple images to be added.
    TileSet(int tileWidth, int tileHeight);

    virtual ~TileSet();

    /// Adds a tile to the set (in case of multi-file tileset).
    void addTile(std::string filePath);

    /// Renders onscreen the tile indexed by #index on #posX and #posY.
    void render(int index, float posX, float posY);

    /// Tells if we're using a single file to contain the tileset or not.
    bool usingSingleFile();

    int getTileWidth();
    int getTileHeight();

private:
    int tileWidth;
    int tileHeight;
    int lines;
    int columns;

    // Tells if we're using a single file to hold the entire tileset.
    // (instead of each tile having it's file)
    bool singleFile;

    // The file where we store the entire tileset
    Sprite* tileSet;

    // Rectangle to clip the sprites on the big image (if we're using
    // a singleFile).
    SDL_Rect* destRect;

    // All tiles loaded from separate files (if we're using several files).
    std::vector<Sprite*> vTiles;
};

#endif /* TILESET_H_DEFINED */
