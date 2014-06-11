#include "charMenu.h"
#include "spriteFactory.h"
#include "characterManager.h"
#include "player.h"
#include "viewport.h"
#include "aaline.h"


CharMenu::CharMenu():
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  gui(),
  charImage(SpriteFrameFactory::getInstance().getFrame("charMenu"))
{
	gui.addButton("archer");
	gui.addButton("warrior");
	gui.addButton("wizard");
	gui.addClicker("CharOff");
	gui.addClicker("charOn");
	gui.addClicker("archeroff");
	gui.addClicker("archeron");
	gui.addClicker("wizardoff");
	gui.addClicker("wizardon");
}

void CharMenu::draw(){
    charImage->draw(0,0);
    gui.draw();
}

