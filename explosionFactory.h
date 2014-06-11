#include "factory.h"

class ExplosionFrameFactory : public AbstractFactory {
public:
  static ExplosionFrameFactory& getInstance();
  ~ExplosionFrameFactory();

  Frame* getFrame(const string& name);
  void setFrame(Frame* const f, const string& name) {
    frames[name] = f;
  }
private:
  const Gamedata& gdata;
  std::map<string, Frame*> frames;
  ExplosionFrameFactory();
  ExplosionFrameFactory(const ExplosionFrameFactory &);
  ExplosionFrameFactory& operator=(const ExplosionFrameFactory &);
};

