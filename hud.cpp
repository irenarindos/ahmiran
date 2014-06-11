#include "hud.h"
#include "spriteFactory.h"
#include "characterManager.h"
#include "player.h"
#include "viewport.h"
#include "aaline.h"



Hud::Hud():
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  hudImage(SpriteFrameFactory::getInstance().getFrame("hud"))
{}

void Hud::draw(){
//Hud will stay in the upper corner of the viewport
	hudImage->draw(Viewport::getInstance().X(),Viewport::getInstance().Y());


//Hud will be implemented as filled bars
    int hp = CharacterManager::getInstance().getPlayer()->getHealthPercentage();
	io.printMessageAt("HP: ", 20, 20);
	//HP bar coords are 50, 52 to 184, 52, length 134
	int hpLength = 50 + (134 * hp);
	if(hpLength < 50) hpLength = 50;
	if(hpLength > 184) hpLength = 184;
        
	Draw_AALine(IOManager::getInstance().getScreen(), 50, 30, hpLength, 30, 8, 0xff0000u); 

	float xp = CharacterManager::getInstance().getPlayer()->getxpPercent();
	io.printMessageAt("XP: ", 20, 45);
	//XP bar coords are 50, 52 to 184, 52
	int xpLength = 50 + (134 * xp);
	if(xpLength<50) xpLength = 50;
	if(xpLength >184) xpLength = 184;

	Draw_AALine(IOManager::getInstance().getScreen(), 50, 52, xpLength, 52, 8, 100u); 
	
	int level = CharacterManager::getInstance().getPlayer()->getLevel();
	io.printMessageValueAt("Level: ", level, 190, 30);

//Print potion amounts
	int potionAmnt = 99;
	io.printMessageValueAt("x ", potionAmnt, 285, 22);
	io.printMessageValueAt("x ", potionAmnt, 285, 54);
}
