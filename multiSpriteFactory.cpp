#include "multiSpriteFactory.h"
#include "ioManager.h"

MultiSpriteFrameFactory& MultiSpriteFrameFactory::getInstance() {
  static MultiSpriteFrameFactory mspriteFactory;
  return mspriteFactory;
}

MultiSpriteFrameFactory::~MultiSpriteFrameFactory() { 
  std::map<string, Frame*>::iterator pos = multiFrames.begin(); 
  while ( pos != multiFrames.end() ) {
    SDL_Surface* surface = pos->second->getSurface();
    SDL_FreeSurface(surface);

    // Note that the order of deletion matters. For example, I can't
    // delete frames before I delete each individual frame.
    const string name = pos->first;
    unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
    unsigned numberOfAnimations = gdata.getXmlInt(name+"Animations");
    Frame *frames = pos->second;
    for (unsigned i = 0; i < numberOfFrames*numberOfAnimations; ++i) {
      frames[i].~Frame();
    }
    operator delete [](frames);
    ++pos;
  }
  multiFrames.clear();
}

MultiSpriteFrameFactory::MultiSpriteFrameFactory() : 
  gdata( Gamedata::getInstance() ),
  multiFrames( std::map<string, Frame*>() ) 
{}

Frame* MultiSpriteFrameFactory::getFrame( const string& name ) {
  std::map<string, Frame*>::iterator pos = multiFrames.find(name); 
  if ( pos == multiFrames.end() ) {
    const string filename = gdata.getXmlStr(name+"File");
    bool alpha = gdata.getXmlBool(name+"Alpha");
    SDL_Surface* surface = IOManager::getInstance().loadAndSet(filename, alpha);
  
    unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
    unsigned numberOfAnimations = gdata.getXmlInt(name+"Animations");
    Uint16 pwidth = gdata.getXmlInt(name+"Width") / numberOfFrames;
    Uint16 pheight = gdata.getXmlInt(name+"Height") / numberOfAnimations;
    Uint16 srcX = gdata.getXmlInt(name+"SrcX");
    Uint16 srcY = gdata.getXmlInt(name+"SrcY");

    // I need to use "operator new" and then "placement new" to
    // avoid calls to the default constructor.
    void *rawMemory = operator new[](numberOfFrames*numberOfAnimations*sizeof(Frame));
    Frame* frames = static_cast<Frame*>(rawMemory);
    for(unsigned i = 0; i < numberOfAnimations; ++i) {
        for(unsigned j = 0; j < numberOfFrames; ++j){
            unsigned frameX = j * pwidth + srcX;
            unsigned frameY = i * pheight + srcY;
            new (&frames[(i*numberOfFrames)+j]) Frame( surface, pwidth, pheight, frameX, frameY);
        }
    }
    multiFrames[name] = frames;
    return frames;
  }
  else return pos->second;
}

