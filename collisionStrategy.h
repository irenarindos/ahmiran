#ifndef COLLISION
#define COLLISION

#include <cmath>
#include "sprite.h"
#include "multiSprite.h"
#include <vector>
using std::vector;

class CollisionStrategy {
public:
  virtual bool execute(const Sprite&, const Sprite&) const = 0;
  virtual bool execute(const MultiSprite&, const MultiSprite&) const =0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual bool execute(const MultiSprite&, const MultiSprite&) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual bool execute(const MultiSprite&, const MultiSprite&) const;
};

#endif
