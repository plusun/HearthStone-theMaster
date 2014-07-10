#ifndef _AI_H_
#define _AI_H_

#include "../logic/player.h"

class AI
{
private:
  int side;
public:
  Player *pl;

  AI(Player *p):
    pl(p)
  {
  }

  void play()
  {
    pl->turn();
    pl->use(0);
      
    int anotherSide;
    for (int i = 0; i < SIDE; ++i)
      if (i != side)
	{
	  anotherSide = i;
	  break;
	}
	  for (int i = -1; i < pl->_battlefield->_minion[pl->side].size(); ++i)
      pl->attack(i, anotherSide, -1);
    pl->over();
  }
  
};

#endif
