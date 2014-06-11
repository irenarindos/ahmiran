#include "gui.h"

Gui::Gui() : 
  io( IOManager::getInstance() ),
  parser( "xmlSpec/menu.xml" ),
  buttons(), 
  clicks(),
  nextIcon(0),
  click(0) 
{
}
 
void Gui::addButton(string name){
  float x = parser.getXmlInt(name+"X");
  float y = parser.getXmlInt(name+"Y");
  string filename = parser.getXmlStr(name+"File");
  SDL_Surface* surfaceNew(io.loadAndSet(filename, true));
  Frame newFrame(surfaceNew, 
            parser.getXmlInt(name+"Width"), 
            parser.getXmlInt(name+"Height"), 
            parser.getXmlInt(name+"SrcX"), 
            parser.getXmlInt(name+"SrcY")); 
  buttons.push_back( Button(name, newFrame, Vector2f(x, y)) );

}

void Gui::addClicker(string name){
  string filename = parser.getXmlStr(name+"File");
  SDL_Surface* surfaceNew(io.loadAndSet(filename, true));
  Frame clickon(surfaceNew, 
            parser.getXmlInt(name+"Width"), 
            parser.getXmlInt(name+"Height"), 
            parser.getXmlInt(name+"SrcX"), 
            parser.getXmlInt(name+"SrcY")); 
  clicks.push_back( clickon );
}

void Gui::draw() const {
  
  buttons[0].frame.draw( buttons[0].position );
  buttons[1].frame.draw( buttons[1].position );
  buttons[2].frame.draw( buttons[2].position );
  Vector2f pos = buttons[nextIcon].position;

//draw below if it's char select menu
  if(buttons[0].name == "archer") clicks[click].draw(pos[0]+50, pos[1]+315);

  else 
	clicks[click].draw(pos[0]-70, pos[1]+20);
}

