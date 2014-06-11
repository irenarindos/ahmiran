#ifndef PLAYER__H
#define PLAYER__H

#include "character.h"
#define LEVELFACTOR 100

/*
 * Class controlled by the player: wizard, warrior, archer
 */
class Player : public Character{

public:
	Player(const string &name): Character(name){}
    ~Player(){}
    
    float neededXP();
    float getxpPercent();
	void updateXP(int gainedPnts); 
	void usePotion(){incrDecrHealth(static_cast<int>(max_hp*.75));}
	
};
#endif
