#include "character.h"
#include "gamedata.h"
#include "clock.h"
#include "characterManager.h"

Character::Character(const string &name) : 
    MultiSprite(name), name(name), 
    attackType(Gamedata::getInstance().getXmlInt(name+"AttackType")),
    atk(Gamedata::getInstance().getXmlInt(name+"Attack")), 
    def(Gamedata::getInstance().getXmlInt(name+"Defense")),
    max_hp(Gamedata::getInstance().getXmlInt(name+"HP")), 
    current_hp(max_hp), 
    max_mp(Gamedata::getInstance().getXmlInt(name+"MP")), 
    current_mp(max_mp), 
    xp(Gamedata::getInstance().getXmlInt(name+"XP")), 
    level(Gamedata::getInstance().getXmlInt(name+"Level")),
    charX(0), charY(0), 
    traveled(0),
    gridPosition(),   
    timeOfDeath(0), 
    attackTimer(0),
    reallyDead(false),
    attackInterval(Gamedata::getInstance().getXmlFloat(name+"AttackInterval"))
{
    setGridCell(Grid::getInstance().getCell(getCenter()));
}

Character::~Character(){}

void Character::update(Uint32 ticks){
    unsigned startFrame = currentAnimation * numberOfFrames;
    unsigned end = (currentAnimation * numberOfFrames) + numberOfFrames - 1;
    if(timeOfDeath > 0){
        if(currentFrame != end){
            float elapsedTime = static_cast<float>(Clock::getInstance().getTicks() - timeOfDeath)/1000.0;
            float interval = static_cast<float>(numberOfFrames) / 16.0;
            if(elapsedTime >= (currentFrame - startFrame) * interval)
                currentFrame++;
        }        
        else {
            reallyDead = true;
            Grid::getInstance().clearCell(gridPosition.getGridRow(), gridPosition.getGridCol());
        }
    }
    else if(attackTimer > 0){
        if(currentFrame != end){
            float elapsedTime = static_cast<float>(Clock::getInstance().getTicks() - attackTimer)/1000.0;
            float interval = static_cast<float>(numberOfFrames) / attackInterval;
            if(elapsedTime >= (currentFrame - startFrame) * interval)
                currentFrame++;
        }
        else endAttack();
    }
    else{
        if(charX == 0 && charY == 0)
            return;

        MultiSprite::advanceFrame(ticks);


        int i, j;
        Cell attempt;
        switch(currentAnimation){
        case NORTH:
            i = gridPosition.getGridRow()-1;
            j = gridPosition.getGridCol();
            break;
        case SOUTH:
            i = gridPosition.getGridRow()+1;
            j = gridPosition.getGridCol();
            break;
        case EAST:
            i = gridPosition.getGridRow();
            j = gridPosition.getGridCol()+1;
            break;
        case WEST:
            i = gridPosition.getGridRow();
            j = gridPosition.getGridCol()-1;
            break;
        default:
            break;
        }
        attempt = Grid::getInstance().getCell(i, j);

        if(attempt.getState() != EMPTY){
            Stop();
            return;
        }

        float newY = Y() + velocityY() * (static_cast<float>(ticks) * 0.001) * charY;
        float newX = X() + velocityX() * (static_cast<float>(ticks) * 0.001) * charX;
        if ( newY < 0 ||  newY > worldHeight-frameHeight)
            charY = 0;
        else Y(newY);

        if ( newX < 0 || newX > worldWidth-frameWidth )
            charX = 0;
        else X(newX);

        Cell current = Grid::getInstance().getCell(getCenter());

        if(!(current == gridPosition)){
            Grid::getInstance().clearCell(gridPosition.getGridRow(), gridPosition.getGridCol());
            gridPosition = attempt;
        }

        Grid::getInstance().occupyCell(gridPosition.getGridRow(), gridPosition.getGridCol(), this);
    }
}

void Character::MoveNorth(){
    attackTimer = 0;
    currentAnimation = NORTH;
    charX = 0;
    charY = -1;
}

void Character::MoveSouth(){
    attackTimer = 0;
    currentAnimation = SOUTH;
    charX = 0;
    charY = 1;
}

void Character::MoveEast(){
    attackTimer = 0;
    currentAnimation = EAST;
    charX = 1;
    charY = 0;
}

void Character::MoveWest(){
    attackTimer = 0;
    currentAnimation = WEST;
    charX = -1;
    charY = 0;
}

void Character::Stop(){
    if(attackTimer == 0 && timeOfDeath == 0){
        currentFrame = currentAnimation * numberOfFrames;
        charX = 0;
        charY = 0;
    }
}

void Character::attack(){
    if(attackTimer == 0){
        currentAnimation += ((numberOfAnimations - numberOfAnimations % 2) / 2);
        currentFrame = currentAnimation * numberOfFrames;
        attackTimer = Clock::getInstance().getTicks();
        Stop();
    }
}

void Character::endAttack(){
    if(attackTimer != 0){
        currentAnimation -= ((numberOfAnimations - numberOfAnimations % 2) / 2);
        attackTimer = 0;
        Stop();
        if(attackType == RANGED){
            CharacterManager::getInstance().newProjectile(name+"Projectile", getCenter(), currentAnimation);
        }
    }
}

void Character::Die(){
    if(timeOfDeath == 0){
        timeOfDeath = Clock::getInstance().getTicks();
        currentAnimation = numberOfAnimations - 1;
        currentFrame = currentAnimation * numberOfFrames;
        current_hp = 0;
    }
}

Vector2f Character::getCenter() const{
    return Vector2f(X()+frameWidth/2, Y()+frameHeight/2); 
}
