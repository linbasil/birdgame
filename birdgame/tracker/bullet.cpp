#include <iostream>
#include <cmath>
#include "bullet.h"
#include "gameData.h"
#include "imageFactory.h"

Bullet::Bullet( const string& name, const Vector2f&  pos,
                          const Vector2f& vel) :
   Sprite(name, pos, vel, ImageFactory::getInstance().getImage(name)),
   distance(0), 
   maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
   tooFar(false) 
{ }

void Bullet::reset() {
  tooFar = false;
  distance = 0;
}

int Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  Sprite::update(ticks);
  if ( getY() < 0 || getY()+getScaledHeight() > worldHeight ) {
    tooFar = true;
  }
  if ( getX() < 0 || getX() > worldWidth ) {
    tooFar = true;
  }  
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
  return 0;
}

