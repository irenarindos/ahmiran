#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_mixer.h>

class SDLSound {
public:
  SDLSound();
  ~SDLSound();

  void startMusic();
  void stopMusic();      // stop all sounds
  void toggleMusic();    // stop all sounds
  void operator[](int);  // play the indexed song
private:
  int volume;
  int currentSong;
  int audioRate;
  int audioChannels;
  int audioBuffers;
  std::vector<const char *> musicFiles; 
  Mix_Music *music;
  //std::vector<Mix_Chunk*> sounds;
  //std::vector<int> channels;
  SDLSound(const SDLSound&);
  SDLSound& operator=(const SDLSound&);
};

