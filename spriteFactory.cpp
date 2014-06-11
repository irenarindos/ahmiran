#include "spriteFactory.h"
#include "ioManager.h"

SpriteFrameFactory& SpriteFrameFactory::getInstance() {
  static SpriteFrameFactory spriteFactory;
  return spriteFactory;
}

SpriteFrameFactory::~SpriteFrameFactory() { 
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);
    delete pos->second;
    ++pos;
  }
  frames.clear();
}

SpriteFrameFactory::SpriteFrameFactory() : 
  gdata( Gamedata::getInstance() ),
  frames( std::map<string, Frame*>() ) 
{}

Frame* SpriteFrameFactory::getFrame( const string& name ) {
  // Frames are stored by filename, which is unique
  std::map<string, Frame*>::iterator pos = frames.find(name); 
  if ( pos == frames.end() ) {
    const string filename = gdata.getXmlStr(name+"File");
    bool alpha = gdata.getXmlBool(name+"Alpha");
    SDL_Surface* surface = IOManager::
      getInstance().loadAndSet(filename, alpha);
  Frame* frame =
    new Frame(surface, 
      gdata.getXmlInt(name+"Width"), gdata.getXmlInt(name+"Height"),
      gdata.getXmlInt(name+"SrcX"), gdata.getXmlInt(name+"SrcY")); 
      frames[name] = frame;
      return frame;
  }
  else return pos->second;
}

