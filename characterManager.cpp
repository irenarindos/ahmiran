#include "vector2f.h"
#include "characterManager.h"
#include "gamedata.h"
#include "viewport.h"
#include <cmath>
#include <iostream>
#include <time.h>

CharacterManager::CharacterManager():
    monsters(),
    dieing(),
    dead(),
    projectiles(),
    explosions(),
    player(),
    collisionCheck(),
    gameGrid(Grid::getInstance()),
    playerCell()
{
    const int NUM = 20;
    string mons[NUM] = {"wolf", "wolf1", "wolf2", "wolf3","boss", "iceWolf", 
                        "evilSquirrel", "evilSquirrel1", "zombie1", 
                        "zombie2", "zombie3", "mimic", "mimic1", "mimic2", 
                        "spiderSmall", "spiderSmall1", "spiderLarge", "gooSoldier", 
                        "gooSoldier1", "spiderLarge1"};
    for(int i = 0; i < NUM; ++i){
        loadXmlEnemy(mons[i]);
    }
}

CharacterManager& CharacterManager::getInstance() {
    static CharacterManager manager;
    return manager;
}

CharacterManager::~CharacterManager() {
    //std::list<Projectile *>::iterator proj;
    std::list<Projectile *>::iterator project;
    std::list<ExplodingSprite *>::iterator explode;
    std::list<Enemy *>::iterator enemy;

    for(enemy = monsters.begin(); enemy != monsters.end(); ++enemy){
        delete *enemy;
    }
    monsters.clear();

    for(enemy = dieing.begin(); enemy != dieing.end(); ++enemy){
        delete *enemy;
    }
    dieing.clear();

    for(enemy = dead.begin(); enemy != dead.end(); ++enemy){
        delete *enemy;
    }
    dead.clear();

    //for(proj = projectiles.begin(); proj != projectiles.end(); ++proj){
    for(project = projectiles.begin(); project != projectiles.end(); ++project){
        delete *project;
    }
    projectiles.clear();

    for(explode = explosions.begin(); explode != explosions.end(); ++explode){
        delete *explode;
    }
	explosions.clear();
}

/*
 * Create and add multiple enemies specified by xml, ensures enemies
 * arent placed on top of each other. Will probably infinite loop if you 
 * try to put too many enemies in too small an area, need to check that
 */
void CharacterManager::loadXmlEnemy(const string &name){
	Enemy *tmp;
    std::list<Enemy *>::iterator enemy;
    int howMany = Gamedata::getInstance().getXmlInt(name+"Num");

    for(int i = 0; i < howMany; ++i){
        tmp = new Enemy(name);
        tmp->Respawn();
        monsters.push_back(tmp);
    }
}

//Checks for collision between character, enemies and projectiles
void CharacterManager::checkForCollisions(){
    std::list<Projectile *>::iterator project;
    std::list<Enemy *>::iterator enemy;
    for(enemy = monsters.begin(); enemy != monsters.end(); ++enemy){
        if(Viewport::getInstance().onScreen((*enemy)->getPosition())){
            Enemy *opponent = *enemy;
            if(collisionCheck.execute((*player), *opponent)){
                //Damage character
	            if(opponent->isAttacking()){
                    int damage = opponent->getAttack() - player->getDefense();
                    player->takeAHit(damage);
                    if(player->isDead())
                        player->Die();
                }

	            //Damage enemy
	            if(player->isAttacking()){
		            int damage = player->getAttack() - opponent->getDefense();
		            opponent->takeAHit(damage);		            
                }
            }   

            //check for enemy collision with projectiles
            for(project = projectiles.begin(); project != projectiles.end(); ++project){
                if(collisionCheck.execute(*(*project), *opponent)){
                    int damage = player->getAttack() - opponent->getDefense();
                    opponent->takeAHit(damage);

                    const Frame* frame = (*project)->getFrame();
                    Sprite sprite((*project)->getPosition(), (*project)->getVelocity(), (*project)->getName(), frame);
	    		    explosions.push_back(new ExplodingSprite(sprite));
                    project = projectiles.erase(project);
                }
            }
            //check is enemy is dead
            if(opponent->isDead()){
                opponent->Die();
                enemy = monsters.erase(enemy);
                dieing.push_back(opponent);
                player->updateXP(opponent->getxp());
            }
        }
   }
   
}

void CharacterManager::update(Uint32 ticks){
    checkForCollisions();

    std::list<ExplodingSprite *>::iterator explode;
    std::list<Projectile *>::iterator project;
    std::list<Enemy *>::iterator enemy;

    Vector2f playerCenter = player->getCenter();
    for(enemy = monsters.begin(); enemy != monsters.end(); ++enemy){
        if(Viewport::getInstance().onScreen((*enemy)->getPosition())){
            //player in sight of enemy
            Vector2f enemyCenter = (*enemy)->getCenter();
		    float dist = Vector2f::distance(enemyCenter,playerCenter);

            //enemy out of patrol zone
            if((*enemy)->getDistanceFromOrigin() > (*enemy)->getRange())
                (*enemy)->Return(ticks);

            else if(dist <= (*enemy)->getSight()){
		    	if(dist <= (*enemy)->attackRange())
                    (*enemy)->attack();

			    else {
                    //Cell adjacent = gameGrid.getAdjacentEmptyCell(player->getGridCell(), 0);
                    //if(adjacent == Cell()) break;
                    (*enemy)->Chase(player->getCenter(), ticks);
                }
		    }

            //all quiet on the western front
            else (*enemy)->Patrol(ticks);

            (*enemy)->update(ticks);
        }
    }

    for(project = projectiles.begin(); project != projectiles.end(); ++project){
        if((*project)->outOfRange()) 
            project = projectiles.erase(project);
        else (**project).update(ticks);
    }


    for(explode = explosions.begin(); explode != explosions.end(); ++explode){
        if ( (*explode)->chunkCount() == 0 )
    		explode = explosions.erase(explode);
        else (*explode)->update(ticks);
    }

    for(enemy = dieing.begin(); enemy != dieing.end(); ++enemy){
        if((*enemy)->isReallyDead()){
            dead.push_back(*enemy);
            enemy = dieing.erase(enemy);            
        }
        else (*enemy)->update(ticks);
    }

	player->update(ticks);
}

void CharacterManager::draw(){
    std::list<ExplodingSprite *>::const_iterator explode;
    std::list<Projectile *>::const_iterator project;
    std::list<Enemy *>::const_iterator enemy;

    for(project = projectiles.begin(); project != projectiles.end(); ++project){
        (**project).draw();
    }
    
    for(explode = explosions.begin(); explode != explosions.end(); ++explode){
        (**explode).draw();
    }

    respawn();
    for(enemy = monsters.begin(); enemy != monsters.end(); ++enemy){
        if(Viewport::getInstance().onScreen((*enemy)->getPosition())){    
            (**enemy).draw();
        }
    }

    for(enemy = dieing.begin(); enemy != dieing.end(); ++enemy){
        (**enemy).draw();
    }
    player->draw();
}

void CharacterManager::respawn(){
    std::list<Enemy *>::iterator enemy;
    for(enemy = dead.begin(); enemy != dead.end(); enemy++){
        Uint32 sinceDeath = Clock::getInstance().getTicks() - (*enemy)->getTimeOfDeath();
        if(sinceDeath/1000 > (*enemy)->getRespawnRate()){
            Enemy *tmp = new Enemy((*enemy)->getName());
            tmp->Respawn();
            monsters.push_back(tmp);
            tmp = *enemy;
            enemy = dead.erase(enemy);
            delete tmp;            
        }
    }
}
