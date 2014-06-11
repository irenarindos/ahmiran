#ifndef ENEMY__H
#define ENEMY__H

#include "character.h"
#include "gamedata.h"
#include "clock.h"

class Enemy : public Character {
    public:
        Enemy(const string &);
        ~Enemy(){}

        //action functions
        void Patrol(Uint32);
        void Chase(const Vector2f &, Uint32);
        void Return(Uint32);
        void Respawn();
        void attack();

        //getters
        float getSight() const
            { return sight; }
        float getRange() const
            { return range; }
        Vector2f getOrigin() const
            { return origin; }
        float getDistanceFromOrigin() const
            { return Vector2f::distance(origin, getPosition()); }
        float attackRange() const
            { return atkRng; }
        Uint32 getRespawnRate() const
            { return respawnRate; }

        //setters
        void setOrigin(const Vector2f &newOrg) 
            { origin = newOrg; }
	private:
        Vector2f origin;
        Vector2f chaseVelocity;
        Vector2f patrolVelocity;
        float range;
        float sight;
		float atkRng;
        Uint32 respawnRate;
};
#endif
