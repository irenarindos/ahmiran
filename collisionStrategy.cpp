#include <algorithm>
#include <vector>
#include "ioManager.h"
#include "collisionStrategy.h"
#include "SDL.h"

using std::cout; using std::endl;

bool RectangularCollisionStrategy::execute(
      const Sprite& obj1, const Sprite& obj2) const {
  float left1 = obj1.X();
  float left2 = obj2.X();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  float top1 = obj1.Y();
  float top2 = obj2.Y();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}

bool RectangularCollisionStrategy::execute(
      const MultiSprite& obj1, const MultiSprite& obj2) const {
  float left1 = obj1.X();
  float left2 = obj2.X();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  float top1 = obj1.Y();
  float top2 = obj2.Y();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}

bool PerPixelCollisionStrategy::execute(
      const Sprite& obj1, const Sprite& obj2) const {
  RectangularCollisionStrategy strategy;
  if ( not strategy.execute(obj1, obj2) ){ return false; }

  Vector2f p1 = obj1.getPosition();
  Vector2f p2 = obj2.getPosition();
  const Frame * const frame1 = obj1.getFrame();
  const Frame * const frame2 = obj2.getFrame();

  int o1Left = p1[0]; 
  int o1Right = o1Left+frame1->getWidth();

  int o2Left = p2[0]; 
  int o2Right = o2Left+frame2->getWidth();

  std::vector<int> x;
  x.reserve(4);
  x.push_back( o1Left );
  x.push_back( o1Right );
  x.push_back( o2Left );
  x.push_back( o2Right );
  std::sort( x.begin(), x.end() );

  int o1Up = p1[1];
  int o1Down = o1Up+frame1->getHeight();
  int o2Up = p2[1];
  int o2Down = o2Up+frame2->getHeight();

  std::vector<int> y;
  y.reserve(4);
  y.push_back( o1Up );
  y.push_back( o1Down );
  y.push_back( o2Up );
  y.push_back( o2Down );
  std::sort( y.begin(), y.end() );

  //surface contains pixel data
  SDL_Surface* surface1 = frame1->getSurface();
  SDL_Surface* surface2 = frame2->getSurface();

  //problems will occur if you dont lock the surface
  SDL_LockSurface(surface1);
  SDL_LockSurface(surface2);


  unsigned pixels1;
  unsigned pixels2;

  for (int i = x[1]; i < x[2]; ++i) {
    for (int j = y[1]; j < y[2]; ++j) {
      pixels1 = obj1.getPixel(i, j);
      pixels2 = obj2.getPixel(i, j);
		
      Uint8 r, g, b;
      Uint8 a1, a2;

      //get alpha value of pixel, store in a1 and a2 respectively
      SDL_GetRGBA(pixels1, surface1->format, &r, &g, &b, &a1);  
      SDL_GetRGBA(pixels2, surface2->format, &r, &g, &b, &a2);

      //collision happens if both are not transparent
      if( a1 > 0 && a2 > 0 ){
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
  }
  SDL_UnlockSurface(surface1);
  SDL_UnlockSurface(surface2);
  return false;
}

bool PerPixelCollisionStrategy::execute(
      const MultiSprite& obj1, const MultiSprite& obj2) const {
  RectangularCollisionStrategy strategy;
  if ( not strategy.execute(obj1, obj2) ){ return false; }

  Vector2f p1 = obj1.getPosition();
  Vector2f p2 = obj2.getPosition();
  const Frame * const frame1 = obj1.getFrame();
  const Frame * const frame2 = obj2.getFrame();

  int o1Left = p1[0]; 
  int o1Right = o1Left+frame1->getWidth();

  int o2Left = p2[0]; 
  int o2Right = o2Left+frame2->getWidth();

  std::vector<int> x;
  x.reserve(4);
  x.push_back( o1Left );
  x.push_back( o1Right );
  x.push_back( o2Left );
  x.push_back( o2Right );
  std::sort( x.begin(), x.end() );

  int o1Up = p1[1];
  int o1Down = o1Up+frame1->getHeight();
  int o2Up = p2[1];
  int o2Down = o2Up+frame2->getHeight();

  std::vector<int> y;
  y.reserve(4);
  y.push_back( o1Up );
  y.push_back( o1Down );
  y.push_back( o2Up );
  y.push_back( o2Down );
  std::sort( y.begin(), y.end() );


  //surface contains pixel data
  SDL_Surface* surface1 = frame1->getSurface();
  SDL_Surface* surface2 = frame2->getSurface();

  //problems will occur if you dont lock the surface
  SDL_LockSurface(surface1);
  SDL_LockSurface(surface2);


  unsigned pixels1;
  unsigned pixels2;

  for (int i = x[1]; i < x[2]; ++i) {
    for (int j = y[1]; j < y[2]; ++j) {
      pixels1 = obj1.getPixel(i, j);
      pixels2 = obj2.getPixel(i, j);
		
      Uint8 r, g, b;
      Uint8 a1, a2;

      //get alpha value of pixel, store in a1 and a2 respectively
      SDL_GetRGBA(pixels1, surface1->format, &r, &g, &b, &a1);  
      SDL_GetRGBA(pixels2, surface2->format, &r, &g, &b, &a2);

      //collision happens if both are not transparent
      if( a1 > 0 && a2 > 0 ){
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        return true;
      }
    }
  }
  SDL_UnlockSurface(surface1);
  SDL_UnlockSurface(surface2);
  return false;
}

