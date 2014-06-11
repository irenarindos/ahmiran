#include "deadMenu.h"
#include "spriteFactory.h"
#include "characterManager.h"
#include "player.h"
#include "viewport.h"


DeadMenu::DeadMenu():
  io( IOManager::getInstance() ),
  deadImage(SpriteFrameFactory::getInstance().getFrame("deadMenu"))
{}

void DeadMenu::draw(){
    deadImage->draw(0,0);
}

