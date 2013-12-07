#ifndef TILEMAP_H_DEFINED
#define TILEMAP_H_DEFINED

#include <vector>
#include <string>
#include "TileSet.hpp"

#include <vector>
#include <string>
#include "TileSet.hpp"

/// Builds the game map in memory, based on the set of tiles available.
//
//  This class has a logic map of the tiles defined by a TileSet.
//  It only contains the indexes of the tiles contained on #TileSet.
//
//  @note You MUST create the #TileSet out of this class and send it
//        as a parameter!
//  @warning The first tile (0, 0) MUST BE A BLANK TILE (empty).
//           Otherwise, this class will interpret that tile as empty
//           anyway.
//           Which means that every time tile (0, 0) appears, it WILL
//           be blank regardless of what image is there.
class TileMap
{
public:
    /// Builds a TileMap completely filled with empty tiles (-1).
    TileMap(int mapWidth, int mapHeight, int layers=1, TileSet* tileSet=NULL);

    /// Builds a TileMap based on the file #mapFile.
    //  @note It MUST be on .tmx format, used by the Tiled editor.
    TileMap(std::string mapFile, TileSet* tileSet=NULL);

    /// Loads a map file on #mapPath.
    //  @note This is called internally, don't worry about it.
    bool load(std::string mapFile);

    /// Reloads the map file stored on the class.
    bool reload();

    /// Associates a new TileSet with the current TileMap.
    void setTileset(TileSet* tileSet);

    /// Shows the TileMap onscreen, based on the TileSet.
    //  @param parallax Tells if we're going to render the map
    //                  with the Parallax effect
    void render(float cameraX=0.0, float cameraY=0.0, bool parallax=false);

    /// Shows only the layer #layer onscreen, based on the TileSet.
    void renderLayer(float cameraX, float cameraY, int layer);

    /// Return the number of layers this TileMap has.
    int  getLayers();

    /// Returns the map width (columns).
    int  getWidth();

    /// Returns the map height (lines).
    int  getHeight();

    /// Returns a reference to the tile index at #x #y #z.
    int& at(int x, int y, int z=0);

    /// Returns a reference to the tile index at #x #y #z.
    std::vector<std::vector<int> > & operator[](int x)
    {
        return (tileMatrix[x]);
    };

private:
    /// Matrix containing the indexes of each tile.
    //  It's a 3-dimension matrix, where x is width, y is height and z
    //  are the layers.
    std::vector <std::vector <std::vector<int> > > tileMatrix;

    /// The current set of tiles we're going to use.
    TileSet* tileSet;

    /// Number of columns of the map.
    int mapWidth;

    /// Number of lines of the map.
    int mapHeight;

    /// Number of layers (depth) of the map.
    int mapLayers;

    /// The current map file.
    std::string mapFile;

    /// Tells if we could load the Tile Map.
    bool loaded;
};

#endif /* TILEMAP_H_DEFINED */
