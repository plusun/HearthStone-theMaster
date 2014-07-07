#ifndef _AI_H_
#define _AI_H_

#include "../logic/player.h"

class AI
{
private:
  Player *pl;
  int side;
public:
  AI(Player *p):
    p(pl)
  {
  }

  void play()
  {
    pl->turn();
    while (pl->use(0))
      ;
    int anotherSide;
    for (int i = 0; i < SIDE; ++i)
      if (i != side)
	{
	  anotherSide = side;
	  break;
	}
    for (int i = -1; i < pl->_battlefield->_minion.size(); ++i)
      pl->attack(i, anotherSide, -1);
    pl->over();
  }
  
};

#endif
