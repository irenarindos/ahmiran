#ifndef SPRITE__H
#define SPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "drawable.h"
#include "frame.h"
#include "spriteFactory.h"

class Sprite : public Drawable {
public:
  Sprite(const string&, AbstractFactory *);
  Sprite(const Sprite& s);
	Sprite(const Vector2f& pos, const Vector2f& vel,
         const string& n, const Frame*);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);
  const string& getName() const { return name; }
  void setName(const string& n) { name = n; }
	void collision() { collided = true; }
	bool hasCollided() { return collided; }

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual unsigned getPixel(Uint32, Uint32) const;
protected:
    string name;
    const Frame * frame;
		bool collided;
  	int getDistance(const Sprite*) const;
};
#endif
