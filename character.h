#ifndef CHARACTER__H
#define CHARACTER__H

#include "multiSprite.h"
#include "grid.h"
#define NORTH 3
#define SOUTH 0
#define EAST 2
#define WEST 1

#define MELEE 0
#define RANGED 1

class Character : public MultiSprite {
	public:
		Character(const string &name);
        virtual ~Character();

        //actions
        virtual void attack();
        virtual void endAttack();
        virtual void MoveWest();
        virtual void MoveEast();
        virtual void MoveNorth();
        virtual void MoveSouth();
        virtual void Stop();
        virtual void Die();
        virtual void update(Uint32);

        //getters
		int getAttack() const
            { return atk; }
		int getDefense() const
            { return def; }
		int getMaxHealth() const
            { return max_hp;  }
        int getCurrentHealth() const
            { return current_hp; } 
	    float getHealthPercentage() const
            { return current_hp/max_hp; }
		int getMaxMana() const
            { return max_mp;  }
        int getCurrentMana() const
            { return current_mp; }
	    int getxp() const
            { return xp; }
    	int getLevel() const
            { return level; }
        const Cell& getGridCell() const
            { return gridPosition; }
        bool isDead() const
	        { return(current_hp <= 0); }
        bool isReallyDead() const   //check if the death animation is over
            { return reallyDead; }
        bool isAttacking() const
            { return(attackTimer != 0); }
        Uint32 getTimeOfDeath() const
            { return timeOfDeath; }
        Vector2f getCenter() const;
             

        //setters
        void setAttack(int atk) 
            { atk = atk; }
        void setDefense(int def) 
            { def = def; }
        void setMaxHealth(int hp) 
            { max_hp = hp; }
        void setCurrentHealth(int hp) 
            { current_hp = hp; }
        void setMaxMana(int mp) 
            { max_mp = mp; }
        void setCurrentMana(int mp) 
            { current_mp = mp; }
        void setGridCell(const Cell &c){ 
            Grid::getInstance().clearCell(gridPosition.getGridRow(), gridPosition.getGridCol());
            gridPosition = c; 
        }
        void incrDecrHealth(int num)
            { current_hp += num; }
        void takeAHit(int num)
            { incrDecrHealth(-num); }

	protected:
		const string name;

        //stats
        int attackType;
		int atk;
		int def;
		int max_hp;
        int current_hp;
		int max_mp;
        int current_mp;
        int xp;
        int level;

        int charX;
        int charY;
        float traveled;
        Cell gridPosition;
        Uint32 timeOfDeath;
        Uint32 attackTimer;
        bool reallyDead;
        float attackInterval;

	private:
		Character();
		Character(const Character& c);
		Character& operator=(const Character&);
};
#endif
