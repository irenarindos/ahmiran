#include "explosionFactory.h"
#include "ioManager.h"

ExplosionFrameFactory& ExplosionFrameFactory::getInstance() {
  static ExplosionFrameFactory fact;
  return fact;
}

ExplosionFrameFactory::~ExplosionFrameFactory() { 
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    // Note that the order of deletion matters. For example, I can't
    // delete frames before I delete each individual frame.
    const string name = pos->first;
    unsigned n = gdata.getXmlInt(name+"Chunks");
    unsigned numberOfFrames = n*n;
    Frame *frames = pos->second;
    for (unsigned i = 0; i < numberOfFrames; ++i) {
      frames[i].~Frame();
    }
    operator delete [](frames);
    ++pos;
  }
  frames.clear();
}

ExplosionFrameFactory::ExplosionFrameFactory() : 
  gdata( Gamedata::getInstance() ),
  frames( std::map<string, Frame*>() ) 
{}

Frame* ExplosionFrameFactory::getFrame( const string& name ) {
  // Frames are stored by filename, which is unique
  std::map<string, Frame*>::iterator pos = frames.find(name); 
  if ( pos == frames.end() ) {
    return NULL;
  }
  else return pos->second;
}

