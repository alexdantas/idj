#include "Music.hpp"
#include "Log.hpp"

Music::Music(std::string filepath)
{
    this->music     = NULL;
    this->setMusic(filepath);
    this->load();
}
Music::~Music()
{
    if (this->music) Mix_FreeMusic(this->music);
}
void Music::setMusic(std::string filepath)
{
    this->filepath = filepath;
}
bool Music::load()
{
    if (!(SDL::hasAudio())) return false;

    if (this->music) Mix_FreeMusic(this->music);

    this->music = Mix_LoadMUS(this->filepath.c_str());
    if (!this->music)
    {
        Log::error("Mix_LoadMUS: Couldn't load music on '" +
                   this->filepath + "'");
        return false;
    }

    Log::debug("Music::load '" + this->filepath + "'");
    return true;
}
bool Music::play(int times)
{
    if (!SDL::hasAudio())
        return false;

    if (!this->music)
        return false;

    if (Mix_PlayMusic(this->music, times))
    {
        Log::error("Mix_PlayMusic: Couldn't play music on '" +
                   this->filepath + "'");
        return false;
    }

//  how can I make it call a member function when done? apparently it
//    doesnt work this way
//    Mix_HookMusicFinished(this->finishedPlaying);

    Log::debug("Music::play");
    return true;
}
void Music::stop()
{
    SDL::stopMusic();
    Log::debug("Music::stop");
}
void Music::pause()
{
    SDL::pauseMusic();
    Log::debug("Music::pause");
}
void Music::unpause()
{
    SDL::resumeMusic();
    Log::debug("Music::unpause");
}
void Music::restart()
{
    this->stop();
    this->play();
}
// void Music::finishedPlaying()
// {
//     this->isPlaying = false;
// }
