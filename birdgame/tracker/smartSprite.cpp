#include <cmath>
#include <random>
#include <functional>
#include <string>
#include "smartSprite.h"
#include "gameData.h"
#include "renderContext.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::goLeft()  { setVelocityX( -abs(getVelocityX()) );  }
void SmartSprite::goRight() { setVelocityX( fabs(getVelocityX()) );  }
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }


SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos, 
  int w, int h, int mode) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(mode),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
{}


SmartSprite::SmartSprite(const SmartSprite& s) : 
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance)
{}

int SmartSprite::update(Uint32 ticks) { 
  TwoWayMultiSprite::update(ticks);
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == 2 ) {
    if(distanceToEnemy < safeDistance) {
      if ( x < ex ) {
        images = imagesRight;
        goRight();
      }
      if ( x > ex ) {
        images = imagesLeft;
        goLeft();
      }
      if ( y < ey ) goDown();
      if ( y > ey ) goUp();
    }
  }
  if  ( currentMode == 0 ) {
    if(distanceToEnemy < safeDistance) currentMode = 1;
  }
  else if  ( currentMode == 1 ) {
    if(distanceToEnemy > safeDistance) currentMode = 0;
    else {
      if ( x < ex ) {
        images = imagesLeft;
        goLeft();
      }
      if ( x > ex ) {
        images = imagesRight;
        goRight();
      }
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
  return 0;
}
