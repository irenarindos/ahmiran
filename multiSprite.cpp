/*
 * Matthew Stratton
 * Project 3
 */

#include "multiSprite.h"
#include "clock.h"
using std::cout; using std::endl;

void MultiSprite::advanceFrame(Uint32 ) {
  static double ms = static_cast<float>(frameInterval)/1000.0;
  Uint32 ticks = Clock::getInstance().getTicks();
  int df = ticks * ms;
  currentFrame = (currentAnimation * numberOfFrames) + (df % numberOfFrames);
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Sprite::update(ticks);
/*
  float height = static_cast<float>(frame->getHeight());
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  if ( Y() + height < 0) {
    Y( Gamedata::getInstance().getXmlInt("worldHeight") );
  }
  if ( Y() > Gamedata::getInstance().getXmlInt("worldHeight")-height) {
    Y( -height );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if ( X() + width < 0) {
    X( Gamedata::getInstance().getXmlInt("worldWidth") );
  }
  if ( X() > Gamedata::getInstance().getXmlInt("worldWidth") ) {
    X( -width );
  }
*/
}

unsigned MultiSprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame[currentFrame].getSurface()->pixels);
  return pixels[ ( y * static_cast<int>(frameWidth) ) + x ];
}
