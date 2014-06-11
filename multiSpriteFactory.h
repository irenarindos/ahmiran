#ifndef MULTISPRITEFRAMEFACTORY__H
#define MULTISPRITEFRAMEFACTORY__H
#include "factory.h"

class MultiSpriteFrameFactory : public AbstractFactory {
public:
  static MultiSpriteFrameFactory& getInstance();
  ~MultiSpriteFrameFactory();

  Frame* getFrame( const string& name );
private:
  const Gamedata& gdata;
  std::map<string, Frame*> multiFrames;
  MultiSpriteFrameFactory();
  MultiSpriteFrameFactory(const MultiSpriteFrameFactory &);
  MultiSpriteFrameFactory& operator=(const MultiSpriteFrameFactory &);
};
#endif
