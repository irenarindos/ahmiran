#ifndef explo
#define explo

#include <iostream>
#include "sprite.h"
#include "spriteFactory.h"
#include "gamedata.h"

class Explosion : public Sprite {
public:
  explicit Explosion(
    const Vector2f& pos, const Vector2f& vel,
    const string& name, const Frame* fm) :
    Sprite(pos, vel, name, fm), 
    worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
    worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
    distance(0.0)
  { 
    X(pos[0]);
    Y(pos[1]);
    velocityX(vel[0]);
    velocityY(vel[1]);
  }
  virtual void update(Uint32 ticks);
  float getDistance() const { return distance; }
  bool outOfBounds() const { 
    bool out = ( X() < 0 || X() > worldWidth || 
                 Y() < 0 || Y() > worldHeight ); 
    return out;
  }
  void reset() {
    distance = 0.0;
  }
private:
  int worldWidth;
  int worldHeight;
  float distance;
};

#endif
