/*
 * useful functions to look in to:
 *     int Mix_FadeOutMusic(int ms)
 *     int Mix_SetMusicPosition(double position)
 *     int Mix_FadeInMusicPos(Mix_Music *music, int loops, int ms, double position)
 *
 * idea:
 *     different Mix_Music for each region (town, adventuring, etc). When a music
 *     switch is made fade music out, halt, fade in new music, resuming its play
 *
 * add sound effects?
 */

#include <ctime>
#include "sound.h"
using std::string;

SDLSound::~SDLSound() {
  Mix_HaltMusic();
  //for (unsigned int i = 0; i < sounds.size(); ++i) {
    //Mix_FreeChunk(sounds[i]);
  //}
  Mix_FreeMusic(music);
  Mix_CloseAudio();
}

SDLSound::SDLSound() : 
  volume(SDL_MIX_MAXVOLUME), 
  currentSong(-1),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  musicFiles(),
  music(NULL)
{
  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, audioBuffers))
    throw string("Unable to open audio!");

/*
 * combine fordlandia/how we left fordlandia into 1 file for adventuring?
 * anyway to tell where we left off?
 */
  musicFiles.push_back("sounds/Fordlandia.ogg"); //adventuring

  music = Mix_LoadMUS(musicFiles[0]);
  if (!music) throw string("Couldn't load: ")+Mix_GetError();
  startMusic();
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
  } 
}

void SDLSound::operator[](int index) {
  if(index == currentSong) return;
  if (currentSong >= 0) Mix_HaltMusic();
  currentSong = index;
  music = NULL;
  music = Mix_LoadMUS(musicFiles[currentSong]);
  if (!music) throw string("Couldn't load: ")+Mix_GetError();
  startMusic();
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

