#ifndef SUBJECTSPRITE__H
#define SUBJECTSPRITE__H

#include <string>
#include <list>
#include <cmath>
#include "player.h"

class SmartSprite;

class SubjectSprite : public Player {
public:
  SubjectSprite(const std::string&);
  SubjectSprite(const SubjectSprite&);

  int update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );

protected:
  std::list<SmartSprite*> observers;
  SubjectSprite& operator=(const SubjectSprite&);
};
#endif
