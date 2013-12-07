#ifndef CONFIG_H_DEFINED
#define CONFIG_H_DEFINED

#include <iostream>
#include <string>
#include "lib/SDL_Config/SDL_config_lib.h"
#include "ConfigDefaults.hpp"

/// This class handles global game customizations and config file.
//
//  To add another customization:
//  * Add it on the class definition
//  * Initialize it with a zero-value at the start of the Config.cpp file
//  * Add default value on a define, on ConfigDefaults.hpp
//  * Start it with the define on reset()
//  * Call the loading function on load()
//  * Add it's call on the program (Config::newCustomization).
//
class Config
{
public:
    Config();

    /// Opens, loads and parses configuration file #fileName.
    static bool load(std::string fileName=DEFAULT_CONFIG_FILE);

    /// Reloads it's configuration file specified on load().
    static bool reload();

    /// Saves all modifications on the opened configuration file.
    static bool save();

    /// Saves all modifications on another file, #fileName.
    static bool saveAs(std::string fileName);

    /// Restarts all values with their hardcoded defaults.
    static void reset();

    static bool debugMode;

    static int screenWidth;
    static int screenHeight;
    static int screenFramerate;
    static int screenBgColorR;
    static int screenBgColorG;
    static int screenBgColorB;

    static std::string audioBg;
    static int         audioRate;

    static float cameraScrollSpeed;

private:
    /// SDL_Config's inner data structure that handles config files.
    static ConfigFile file;

    /// Original configuration file's name.
    //  Contains the last file name passed to #load.
    static std::string filename;
};

#endif /* CONFIG_H_DEFINED */



