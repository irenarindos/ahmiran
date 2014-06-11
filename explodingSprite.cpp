#include <iostream>
#include <cmath>
using std::cout; using std::endl;
#include "explodingSprite.h"
#include "ioManager.h"
#include "explosionFactory.h"
#include "gamedata.h"

const int DIRECTION_MOD = 100;
const int MAX_EXPLOSION_SPD = 200;
const int MIN_EXPLOSION_SPD = 40;

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  Sprite(s), 
  screen(IOManager::getInstance().getScreen()), 
  frame(s.getFrame()),
  spriteSurface(frame->getSurface()), 
  chunks(), 
  freeList() {
  makeChunks(Gamedata::getInstance().getXmlInt(getName()+"Chunks"));
}

ExplodingSprite::~ExplodingSprite() { 
  chunks.clear();
  freeList.clear();
}

void ExplodingSprite::draw() const { 
  for (unsigned int i = 0; i < chunks.size(); ++i) {
    chunks[i].draw();
  }
}

void ExplodingSprite::update(Uint32 ticks) { 
  // Compare vector performance to list because we remove from middle!
  vector<Explosion>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->outOfBounds() || ptr->getDistance() > 50) {
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
}

Vector2f ExplodingSprite::getNewVelocity() const {
  // These are used to calculate the direction of the chunk velocity 
  // and have no bearing on its magnitude
  float x_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);
  float y_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);

  // The if statement makes sure we don't try to normalize a Vector2f(0,0) 
  // (which will give a runtime crash)
  if (fabs(x_dir) < 0.001 && fabs(y_dir) < 0.001) {
    x_dir += rand()%2?-1:1;
    y_dir += rand()%2?-1:1;
  }

  // This vector will eventually hold the velocity, 
  // it now holds just the direction:
  Vector2f velocity(x_dir, y_dir);   

  // We normalize to get rid of the magnitude of the above calculations, 
  // but keep direction:
  velocity = velocity.normalize();   

  // Now compute a random speed between MIN_EXPLOSION_SPD and
  // MAX_EXPLOSION_SPD
  int speed = (rand() % (MAX_EXPLOSION_SPD - MIN_EXPLOSION_SPD)) 
              + MIN_EXPLOSION_SPD;

  // We now scale the unit-length direction of velocity by the speed above
  velocity *= speed;

  // velocity is now a random Vector2f in 360 degrees,
  // with magnitude between the min and max speeds.
  return velocity;
}

Frame* ExplodingSprite::makeChunkFrames(unsigned n) { 
  unsigned chunk_width = frame->getWidth()/n;
  unsigned chunk_height = frame->getHeight()/n;
  Sint16 source_x = frame->getSourceX();
  Sint16 source_y = frame->getSourceY();

  void *rawMemory = operator new[](n*n*sizeof(Frame));
  Frame* frames = static_cast<Frame*>(rawMemory);
  unsigned count = 0;
  for (unsigned i = 0; i < n; ++i) {
    for (unsigned j = 0; j < n; ++j) {
      new (&frames[count++]) Frame(spriteSurface, chunk_width, chunk_height,
           source_x+i*chunk_width,  // x coord of surface
           source_y+j*chunk_height); // y coord of surface
    }
  }
  return frames;
}

void ExplodingSprite::makeChunks(unsigned n) { 
  unsigned chunk_width = frame->getWidth()/n;
  unsigned chunk_height = frame->getHeight()/n;
  Frame* chunkFrames =
    ExplosionFrameFactory::getInstance().getFrame(getName());
  if ( chunkFrames == NULL ) {
    chunkFrames = makeChunkFrames(n);
    ExplosionFrameFactory::getInstance().setFrame(chunkFrames, getName());
  }

  float x = X();
  float y = Y();
  unsigned chunkCount = 0;
  for (unsigned i = 0; i < n; ++i) {
    for (unsigned j = 0; j < n; ++j) {
      Explosion explosion(
                Vector2f(x+i*chunk_width,   // x coord of destination 
                         y+j*chunk_height), // y coord of destination
                getNewVelocity(),
                getName(),
                &chunkFrames[chunkCount++]
                );
      chunks.push_back(explosion);
    }
  }
}

