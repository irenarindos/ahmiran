#include "frame.h"
#include "viewport.h"
#include "gamedata.h"

class World {
public:
  World(const string &name, int fact = 1) : 
      frame1(*SpriteFrameFactory::getInstance().getFrame(name)), 
      frame2(*SpriteFrameFactory::getInstance().getFrame(name)), 
      frameWidth( frame1.getWidth() ),
      worldWidth( Gamedata::getInstance().getXmlInt("worldWidth") ),
      factor(fact),
      worldX(0.0), worldY(0.0), 
      view(Viewport::getInstance()) 
  {}
  void update();
  void draw() const;
private:
  Frame const frame1;
  Frame const frame2;
  unsigned frameWidth;
  unsigned worldWidth;
  int factor;
  float worldX;
  float worldY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};
