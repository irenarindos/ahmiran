#ifndef STARTMENU__H
#define STARTMENU__H

#include <iostream>
#include <string>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "frame.h"
#include "gui.h"


class StartMenu {
public:
  StartMenu();
  ~StartMenu() {};

  const IOManager& io;
  Clock& clock;

  void draw();
  bool loop(bool &done, bool &secondMenu);

  void dec(){gui.decrement();}
  void inc(){gui.increment();}
  void lightOn(){gui.lightOn();}
  void lightOff(){gui.lightOff();}
  void reset(){ gui.reset(); }

    Gui gui;

private:
    Frame * startImage;
    StartMenu(const StartMenu&);
    StartMenu& operator=(const StartMenu&);
};

#endif
