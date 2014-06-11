/*
 * Matthew Stratton
 * Project 3
 */

#include <SDL.h>
#include <iostream>
#include <string>
#include <list>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "sprite.h"
#include "world.h"
#include "viewport.h"
#include "multiSprite.h"
#include "spriteFactory.h"
#include "multiSpriteFactory.h"
#include "player.h"
#include "enemy.h"
#include "characterManager.h"
#include "hud.h"
#include "startMenu.h"
#include "sound.h"
#include "deadMenu.h"
#include "charMenu.h"

class Manager {
	public:
  	Manager ();
  	~Manager ();
  	void play();

	private:
  	const bool env;
  	const IOManager& io;
  	Gamedata& gdata;
  	Clock& clock;
	Viewport& view;

  	SDL_Surface * screen;
    Player *player;
    CharacterManager &man;
    World map;  
	Hud hud;
	StartMenu startMenu;
	DeadMenu deadMenu;
	CharMenu charMenu;
	SDLSound sound;

  	void draw();
	void drawStartScreen();
	void update();
  	Manager(const Manager&);
  	Manager& operator=(const Manager&);
};
