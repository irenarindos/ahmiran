#include "enemy.h"
#include "vector2f.h"
#include "grid.h"
#include "player.h"
#include "characterManager.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(const string &name):
    Character(name), 
    origin(X(), Y()), 
    chaseVelocity(velocityX(), velocityY()),
    patrolVelocity(Gamedata::getInstance().getXmlInt(name+"PatrolXspeed"),
                   Gamedata::getInstance().getXmlInt(name+"PatrolYspeed")),
    range(Gamedata::getInstance().getXmlFloat(name+"PatrolRange")), 
    sight(Gamedata::getInstance().getXmlFloat(name+"Sight")),
	atkRng(Gamedata::getInstance().getXmlFloat(name+"AttackRange")),
    respawnRate(Gamedata::getInstance().getXmlInt(name+"Respawn")){}

void Enemy::attack(){
    if(attackTimer == 0){
        Player *player = CharacterManager::getInstance().getPlayer();
        Vector2f playerCenter = player->getCenter();
    
        //determine which direction player is facing relative to enemy
        float x = playerCenter[0] - getCenter()[0];
        float y = playerCenter[1] - getCenter()[1];
        int dir = -1;
        if(std::abs(x) > std::abs(y)){
            if(x < 0) dir = WEST;
            else dir = EAST;
        }
        else{
            if(y < 0) dir = NORTH;
            else dir = SOUTH;
        }

        currentAnimation = dir + ((numberOfAnimations - numberOfAnimations % 2) / 2);
        currentFrame = currentAnimation * numberOfFrames;
        attackTimer = Clock::getInstance().getTicks();
        Stop();
    }
}

void Enemy::Patrol(Uint32 ticks){
    //std::cout << "Patroling!" << std::endl;
    setVelocity(patrolVelocity);
    Vector2f dist = getVelocity() * (static_cast<float>(ticks) * 0.001);
    traveled += dist.magnitude();
 
    if(traveled >= (static_cast<float>(Grid::getInstance().getCellSize()) * (rand()%2+1))){
        traveled = 0.0;
        if(rand()%2) Stop();
        else{
            
            float newX, newY;
       
            //randomize position
            if(rand()%2) newX = X() + rand()%static_cast<int>(getRange());
            else newX = X() - rand()%static_cast<int>(getRange()); 
            if(rand()%2) newY = Y() + rand()%static_cast<int>(getRange());
            else newY = Y() - rand()%static_cast<int>(getRange());

            Cell target = Grid::getInstance().getCell(Vector2f(newX, newY));
            Cell move = Grid::getInstance().path(getCenter(), target.getCenter());

            if(move == gridPosition){
                Stop();                
                return;
            }

            float x = move.getCenter()[0] - gridPosition.getCenter()[0];
            float y = move.getCenter()[1] - gridPosition.getCenter()[1];

            if(y == 0){
                if(x < 0) MoveWest();
                else MoveEast();
            }
            else{
                if(y < 0) MoveNorth();
                else MoveSouth();
            }
        }
    }
}

void Enemy::Chase(const Vector2f &pos, Uint32 ticks){
    //std::cout << "Chasing!" << std::endl;
    setVelocity(chaseVelocity);
    Vector2f dist = getVelocity() * (static_cast<float>(ticks) * 0.001);
    traveled += dist.magnitude();
 
    if(traveled >= static_cast<float>(Grid::getInstance().getCellSize())){
        traveled = 0.0;
        Cell move = Grid::getInstance().path(gridPosition.getCenter(), pos);
        //std::cout << "Chasing point " << pos[0] << ", " << pos[1] << std::endl;        
        //move.print();
        if(move == gridPosition){
            Stop();
            return;
        }
        float x = move.getCenter()[0] - gridPosition.getCenter()[0];
        float y = move.getCenter()[1] - gridPosition.getCenter()[1];

        if(y == 0){
            if(x < 0) MoveWest();
            else MoveEast();
        }
        else{
            if(y < 0) MoveNorth();
            else MoveSouth();
        }
    }
}

void Enemy::Return(Uint32 ticks){
    //std::cout << "Returning!" << std::endl;
    Vector2f dist = getVelocity() * (static_cast<float>(ticks) * 0.001);
    traveled += dist.magnitude();

    if(traveled >= static_cast<float>(Grid::getInstance().getCellSize())){
        traveled = 0.0;
        Cell move = Grid::getInstance().path(gridPosition.getCenter(), origin);
        //move.print();
        if(move == gridPosition){
            Stop();
            return;
        }

        float x = move.getCenter()[0] - gridPosition.getCenter()[0];
        float y = move.getCenter()[1] - gridPosition.getCenter()[1];

        if(y == 0){
            if(x < 0) MoveWest();
            else MoveEast();
        }
        else{
            if(y < 0) MoveNorth();
            else MoveSouth();
        }
    }
}

void Enemy::Respawn(){
    timeOfDeath = 0;
    reallyDead = false;
    current_hp = max_hp;
    currentAnimation = 0;
    currentFrame = 0;
    Cell *c = NULL;
    do{
        float newX, newY;
       
        //randomize position
        if(rand()%2) newX = X() + rand()%static_cast<int>(getRange());
        else newX = X() - rand()%static_cast<int>(getRange()); 
        if(rand()%2) newY = Y() + rand()%static_cast<int>(getRange());
        else newY = Y() - rand()%static_cast<int>(getRange());

        //std::cout << "Center: " << center[0] << ", " << center[1] << std::endl;
        c = new Cell(Grid::getInstance().getCell(Vector2f(newX, newY)));
        //std::cout << "Grid point: " << c->getGridRow() << ", " << c->getGridCol() << std::endl;
        if(c->getState() != EMPTY)
            c = NULL;
    } while(c == NULL);

    gridPosition = *c;
    setPosition(gridPosition.getCenter());
    origin = gridPosition.getCenter();
    Grid::getInstance().occupyCell(gridPosition.getGridRow(), gridPosition.getGridCol(), this);
}
