#ifndef MUSIC_H_DEFINED
#define MUSIC_H_DEFINED

#include "SDL.hpp"

/// Loads and plays a music.
///
/// @note We can only have one music playing at the same time.
/// @note Tested with .ogg and .mp3 formats.
///
/// ## Usage
///     Music music("path/to/music.mp3");
///     music.play();
///
/// ## For developers
/// This is almost a standalone class. It depends on SDL, that
/// handles low-level SDL calls.
///
/// But this class can be easily reused on your project if you change
/// the right methods.
///
/// One interesting thing is that SDL can be used for simple audio
/// management without necessarily interfering with graphics.
///
/// For instance, I've made a ncurses game (full console, no graphics)
/// with SDL audio.
///
class Music
{
public:
    /// Initializes pretty much everything.
    ///
    /// Yeah, don't bother calling any of the functions below unless
    /// you want to override the music filepath.
    Music(std::string filepath);

    virtual ~Music();

    /// Loads the music into memory.
    ///
    /// This is automatically called when the class is initialized.
    /// @note The only reason you should call this song is in case
    ///       you've changed the music with setMusic().
    bool load();

    /// Sets the current music to be the one on `filepath`.
    ///
    /// @note Must call load() to reload the song!
    void setMusic(std::string filepath);

    /// Plays the loaded music.
    ///
    /// @param times How many times we'll play the music. If -1,
    ///              infinite loop.
    bool play(int times=-1);

    /// Stops the music (along with all musics currently playing).
    ///
    /// The problem with Mix's API is that when I tell it to
    /// stop playing music, it stops all musics currently playing
    void stop();

    /// Pauses the music (along with all musics currently playing).
	void pause();

    /// Unpauses the music (along with all musics currently playing).
    void unpause();

    /// Restarts the music.
    ///
    /// @note Stops all musics that are currently playing but restarts
    ///       only the current song.
    void restart();

    //  This function's called automatically when the music stops.
    //  It warns internally that the music has stopped.
    //  @note Don't you dare call it! False alarms are not welcome.
    //
    //  @bug Mix doesn't allow you to define a callback liek this.
    //       what should I do?
    //void finishedPlaying();

private:
    /// Internal SDL data structure that takes care of music.
    Mix_Music*  music;

    /// The file path of the music currently loaded.
    std::string filepath;

    /// Tells if the music's playing.
    bool        isPlaying;
};

#endif /* MUSIC_H_DEFINED */
