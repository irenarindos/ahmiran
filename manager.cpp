/*
 * Matthew Stratton
 * Project 3
 */

#include <cmath>
#include "manager.h"

Manager::~Manager() {
   if(player != NULL) delete player;
}

Manager::Manager() :
    env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	io( IOManager::getInstance() ),
 	gdata( Gamedata::getInstance() ),
 	clock( Clock::getInstance() ),
	view(Viewport::getInstance()),
 	screen( io.getScreen() ),
    player(),
    man(CharacterManager::getInstance()),
    map("worldMap"),
	hud(),
    startMenu(),
	deadMenu(),
	charMenu(),
	sound()   
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		throw string("Unable to initialize SDL: ");
 	}
 	atexit(SDL_Quit);
}

void Manager::draw() {
  map.draw();
  man.draw();
  gdata.incrFrames();
  hud.draw();
}

void Manager::update(){
	Uint32 ticks = clock.getElapsedTicks();
  view.update();
  map.update();
  man.update(ticks);
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  bool startScreen = true;
  bool keyCatch = false;
  bool returnKey = false;
  bool KEYS[322];
  for(int i = 0; i < 322; ++i){
    KEYS[i] = false;
  }
  bool secondMenu = false;
  bool gameOn = false;  
  charMenu.gui.archerOn();

  while ( not done ) {
	    SDL_PollEvent(&event);
   	    if (event.type ==  SDL_QUIT) { done = true;}
        //start menu
    	if(startScreen){
   	        if(event.type == SDL_KEYDOWN) {
     	        switch ( event.key.keysym.sym ) {
            	    case SDLK_ESCAPE : done = true; break;
       	      	    case SDLK_q      : done = true; break;
       	       	    case SDLK_RETURN : {
                        if ( !keyCatch ) { startMenu.lightOn();returnKey = true; } 
                        break; 
                    }
           	 	    case SDLK_DOWN   : {
                        if ( !keyCatch ) {startMenu.inc();} 
		                break; 
                    }
                	case SDLK_UP   : {
                        if ( !keyCatch ) { startMenu.dec();}
    		            break; 
                    }
                	default          : break;
                }//end switch
      	        keyCatch = true;
       	    }//end keydown
            if(event.type == SDL_KEYUP) { 
         	    keyCatch = false; 
          	    if ( returnKey ) {
                    string option = startMenu.gui.getIconClicked();
                    if(option == "new"){secondMenu = true; startScreen = false;}
     	            if(option == "exit"){done = true; startScreen = false;}
     	            if(option == "open")	 //do nothing for now
                    startMenu.lightOff();
       	            keyCatch = false;
                    returnKey = false;
                }
            }//end keyup
	        startMenu.draw();
        }//end startmenu

        //char select menu
        if(secondMenu){

            charMenu.draw();  
   	        if (event.type ==  SDL_QUIT) { done = true;}
   	        if(event.type == SDL_KEYDOWN) {
     	        switch ( event.key.keysym.sym  ) {
       	        	case SDLK_ESCAPE : done = true; break;
       	         	case SDLK_q      : done = true; break;
       	         	case SDLK_RETURN : {
                        if ( !keyCatch ) {returnKey = true; } 
		                break; 
                    }
       	 	        case SDLK_LEFT  : {
        	            if ( !keyCatch ) {
                            charMenu.inc();
    		                int click = charMenu.gui.getClick();
	                		if(click ==0) {charMenu.gui.wizardOn();}
	                		if(click ==2){charMenu.gui.lightOff();}
	                		if(click ==4){charMenu.gui.archerOn();}
	            		}
		                break; 
                    }
        	        case SDLK_RIGHT  : {
          	            if ( !keyCatch ) { 
                            charMenu.dec();
		                    int click = charMenu.gui.getClick();
			                if(click ==0) {charMenu.gui.archerOn();}
                			if(click ==2){charMenu.gui.wizardOn();}
                			if(click ==4){charMenu.gui.lightOff();}
            			}
		                break; 
                    }
                	default          : break;
      	        }//end switch
      	        keyCatch = true;
   	        }//end keydown
   	        if(event.type == SDL_KEYUP) { 
     	        keyCatch = false; 
      	        if ( returnKey ) {
                    string option = charMenu.gui.getIconClicked();
     	            if(option == "archer"){player = new Player("archer");}
     	            if(option == "player"){player = new Player("player");}
     	            if(option == "wizard"){player = new Player("wizard");}	
    		        view.setObjectToTrack(player); 
    		        man.registerPlayer(player);
	                secondMenu = false;
	                gameOn = true;
                    charMenu.lightOff();
	                keyCatch = false;
                    returnKey = false;
                }
            }//end keyup
        }//end char select menu
  if(gameOn) draw();
  SDL_Flip(screen);
  if(gameOn){
    update();

    //get what keys are pressed
    while(SDL_PollEvent(&event)){
      switch (event.type) {
        case SDL_QUIT: done = true; break;
        case SDL_KEYDOWN:
          KEYS[event.key.keysym.sym] = true;keyCatch = false;break;
        case SDL_KEYUP:
          KEYS[event.key.keysym.sym] = false;keyCatch = true;break;
        case SDL_MOUSEBUTTONDOWN:break;
        default: break;
      }
    }
    
    //non-ghosting
    if(!keyCatch){
      keyCatch = true;
      if(KEYS[SDLK_ESCAPE] || KEYS[SDLK_q]) done = true;
      if(KEYS[SDLK_p]){
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if(KEYS[SDLK_m]) sound.toggleMusic();
      if(KEYS[SDLK_1] && !player->isDead())player->usePotion();
    }

    //ghosting
    if(!player->isDead()){	
        if(KEYS[SDLK_SPACE]) player->attack();
        else if(KEYS[SDLK_UP] || KEYS[SDLK_w]) player->MoveNorth();
        else if(KEYS[SDLK_DOWN] || KEYS[SDLK_s]) player->MoveSouth(); 
        else if(KEYS[SDLK_LEFT] || KEYS[SDLK_a]) player->MoveWest();
        else if(KEYS[SDLK_RIGHT] || KEYS[SDLK_d]) player->MoveEast();
        else player->Stop();
    }

    if(player->isReallyDead()){
        gameOn = false;
        startScreen = true;
        secondMenu = false;
        delete player;
        player = NULL;
        startMenu.draw();
        view.X(0);
        view.Y(0);
        charMenu.gui.archerOn();
        charMenu.reset();
        startMenu.lightOff();
        startMenu.reset();
    }
  }
 }//end while
}
