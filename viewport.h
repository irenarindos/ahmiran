#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
#include "gamedata.h"

class Viewport {
	public:
  		static Viewport& getInstance();
  		void update();
  		void setObjExploded();

  		float X() const { return position[0]; }
  		void X(float x) { position[0] = x; }
  		float Y() const { return position[1]; }
  		void Y(float y) { position[1] = y; }

  		void setObjectToTrack(const Sprite *obj);
  		const Sprite* getObjectToTrack() const { return objectToTrack; } 
  		void freeze() { frozen = true; }
  		void draw(Uint32) const;
        unsigned getViewWidth(){ return viewWidth; }
        unsigned getViewHeight(){ return viewHeight; }
        bool onScreen(const Vector2f &pos){
            if(pos[0] < position[0] - 200 || pos[0] > position[0]+viewWidth+200 ||
               pos[1] < position[1] - 200 || pos[1] > position[1]+viewHeight+200)
                return false;
            return true;
        }
	private:
  		bool frozen;
  		const Gamedata& gdata;
  		Vector2f position;
  		unsigned viewWidth;
  		unsigned viewHeight;
  		unsigned worldWidth;
  		unsigned worldHeight;
  		Uint16 objWidth;
  		Uint16 objHeight;
  		int objX;
  
  		const Sprite *objectToTrack;

  		Viewport();
  		Viewport(const Viewport&);
  		Viewport& operator=(const Viewport&);
};
#endif
