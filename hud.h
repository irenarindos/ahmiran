#ifndef HUD__H
#define HUD__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "frame.h"


class Hud {
public:
  Hud();
  ~Hud() {};

  const IOManager& io;
  Clock& clock;

  void draw();

private:
    Frame * hudImage;
    Hud(const Hud&);
    Hud& operator=(const Hud&);
};

#endif
