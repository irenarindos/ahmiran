#include "projectile.h"	

Projectile::Projectile(const string &n, const Vector2f &ori, int dir): 
    MultiSprite(n),
    maxDistance(Gamedata::getInstance().getXmlFloat(n+"Range")),
	traveled(0.0),
    origin(ori),
    charX(0), charY(0)
{ 
    currentFrame = dir; 
    setPosition(origin);
    switch(dir){
    case NORTH:
         charX = 0; charY = -1;
        break;
    case SOUTH:
        charX = 0; charY = 1;
        break;
    case EAST:
        charX = 1; charY = 0;
        break;
    case WEST:
        charX = -1; charY = 0;
        break;
    }
}

void Projectile::update(Uint32 ticks){
    Vector2f dist = getVelocity() * (static_cast<float>(ticks) * 0.001);
    traveled += dist.magnitude();
	
    float incr = velocityY() * charY * static_cast<float>(ticks) * 0.001;
    if ( Y()+incr < 0 ||  Y()+incr > worldHeight-frameHeight)
        charY = 0;
    else Y(Y()+incr);

    incr = velocityX() * charX * static_cast<float>(ticks) * 0.001;
    if ( X()+incr < 0 || X()+incr > worldWidth-frameWidth )
        charX = 0;
    else X(X()+incr);
}

bool Projectile::outOfRange(){
    return (traveled > maxDistance || 
            X() < 0 || X() > worldWidth - frameWidth || 
		    Y() < 0 || Y() > worldHeight - frameHeight);
}

void Projectile::print(){
    std::cout << name << std::endl;
    std::cout << "\tOrigin: " << origin[0] << ", " << origin[1] << std::endl;
    std::cout << "\tPosition: " << X() << ", " << Y() << std::endl;
    std::cout << "\tVelocity: " << getVelocity()[0] << ", " << getVelocity()[1] << std::endl;
}
