#ifndef CHARMENU__H
#define CHARMENU__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "frame.h"
#include "gui.h"


class CharMenu {
public:
  CharMenu();
  ~CharMenu() {};

  const IOManager& io;
  Clock& clock;

  void draw();

  void dec(){gui.decrement();}
  void inc(){gui.increment();}
  void lightOn(){gui.lightOn();}
  void lightOff(){gui.lightOff();}
  void reset(){ gui.reset(); }

  Gui gui;

private:
    Frame * charImage;
    CharMenu(const CharMenu&);
    CharMenu& operator=(const CharMenu&);
};

#endif
