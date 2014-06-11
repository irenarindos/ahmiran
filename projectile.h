/*
 * Matthew Stratton
 * Project 4
 */

#ifndef proj
#define proj
#include "multiSprite.h"
#include "vector2f.h"
#include "gamedata.h"
#include "character.h"

class Projectile : public MultiSprite{
  public:
    Projectile(const string &n, const Vector2f &ori, int dir);
	void update(Uint32 ticks);
    bool outOfRange();
    void print();
  private:
    float maxDistance;
	float traveled;
    Vector2f origin;
    int charX;
    int charY;
    
    Projectile(const Projectile &);
    Projectile();
    Projectile& operator=(const Projectile&);
};
#endif
