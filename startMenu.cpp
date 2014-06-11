#include "startMenu.h"
#include "spriteFactory.h"
#include "characterManager.h"
#include "player.h"
#include "viewport.h"
#include "aaline.h"
#include <SDL.h>


StartMenu::StartMenu():
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  gui(),
  startImage(SpriteFrameFactory::getInstance().getFrame("startMenu"))
{
	gui.addButton("new");
	gui.addButton("open");
	gui.addButton("exit");
	gui.addClicker("clickoff");
	gui.addClicker("clickon");
}

void StartMenu::draw(){
    startImage->draw(0,0);
    gui.draw();
}

bool StartMenu::loop(bool &done, bool &secondMenu){
  SDL_Event event;
  bool keyCatch = false;
  bool returnKey = false;
    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { done = true; return false;}
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            lightOn();
            returnKey = true; } break; }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {inc();} break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) { dec();}break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      if ( returnKey ) {
        string option = gui.getIconClicked();
     	if(option == "new"){
	   secondMenu = true;
           return false;
         }
     	if(option == "exit"){
           done = true;
	   return false;	  
         }
     	if(option == "open"){
	  //do nothing for now
        }
        lightOff();
    }
   }

   return true;
}
