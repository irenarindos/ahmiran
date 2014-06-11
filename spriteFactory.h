#ifndef spffact
#define spffact

#include "factory.h"

class SpriteFrameFactory : public AbstractFactory {
  public:
    static SpriteFrameFactory& getInstance();
    ~SpriteFrameFactory();

    Frame* getFrame(const string & name);
  private:
    const Gamedata& gdata;
    std::map<string, Frame*> frames;
    SpriteFrameFactory();
    SpriteFrameFactory(const SpriteFrameFactory &);
    SpriteFrameFactory& operator=(const SpriteFrameFactory &);
};
#endif
