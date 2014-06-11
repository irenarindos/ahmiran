#include "player.h"
#include "clock.h"
#include "characterManager.h"
#include <iostream>

float Player::neededXP(){
    float sum(0.0);
    for(int i = 1; i <= level+1; ++i){
        sum += i * 100;
    }
    return sum;
}

float Player::getxpPercent(){
   return xp/neededXP();
}

void Player::updateXP(int gainedPnts){
    //Gained points is a measure of enemy difficulty
	xp += gainedPnts;

    //using xp = 10 x current level
	if(xp >= neededXP()){
        ++level;
        atk += 2;
        def += 2;
        current_hp = max_hp += 10;
        current_mp = max_mp += 10;
    }
}
