#ifndef DEADMENU__H
#define DEADMENU__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "frame.h"


class DeadMenu {
public:
  DeadMenu();
  ~DeadMenu() {};

  const IOManager& io;
  void draw();

private:
    Frame * deadImage;
    DeadMenu(const DeadMenu&);
    DeadMenu& operator=(const DeadMenu&);
};

#endif
