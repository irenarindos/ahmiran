/*
 * Matthew Stratton
 * Project 3
 */

#ifndef multisprt
#define multisprt

#include <iostream>
#include "sprite.h"
#include "gamedata.h"
#include "multiSpriteFactory.h"

class MultiSprite : public Sprite {
public:
  MultiSprite( const string& name ) : 
    Sprite( name, &MultiSpriteFrameFactory::getInstance() ),
    currentFrame(0), currentAnimation(0),
    numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
    numberOfAnimations( Gamedata::getInstance().getXmlInt(name+"Animations") ),
    frameInterval(Gamedata::getInstance().getXmlInt(name+"FrameInterval")),
    frameWidth( frame->getWidth() ), frameHeight( frame->getHeight() ),
    worldWidth( Gamedata::getInstance().getXmlInt("worldWidth") ),
    worldHeight( Gamedata::getInstance().getXmlInt("worldHeight") )
  {}

  virtual const Frame* getFrame() const { return &frame[currentFrame]; }
  virtual void draw() const { frame[currentFrame].draw(X(), Y()); }
  virtual void update(Uint32 ticks);
  Vector2f getCenter(){
    return Vector2f( X()+frameWidth/2, Y()+frameHeight/2 );
  }

  unsigned getPixel(Uint32, Uint32) const;

protected:
  unsigned currentFrame;
  unsigned currentAnimation;
  unsigned numberOfFrames;
  unsigned numberOfAnimations;
  unsigned frameInterval;
  float frameWidth;
  float frameHeight;
  int worldWidth;
  int worldHeight;

  virtual void advanceFrame(Uint32);
private:
  MultiSprite(const MultiSprite&);
  MultiSprite& operator=(const MultiSprite&);
};

#endif
