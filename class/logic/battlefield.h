#ifndef _CLASS_BATTLEFIELD_
#define _CLASS_BATTLEFIELD_

#include "basic.h"
#include "character.h"

#define SIDE 2

class Battlefield
{
public:
  vector<Minion *> _minion[SIDE];
  Hero *_hero[SIDE];
  Battlefield(){};
  Battlefield(Hero *one, Hero *another)
  {
    _hero[0] = one;
    _hero[1] = another;
  }
  ~Battlefield()
  {
    for (int i = 0; i < SIDE; ++i)
      for (vector<Minion *>::iterator itr = _minion[i].begin();
	   itr != _minion[i].end();
	   ++itr)
	if (*itr != NULL)
	  delete *itr;
    for (int i = 0; i < SIDE; ++i)
      if (_hero[i] != NULL)
	delete _hero[i];
  }

  void summon_minion(Minion* m, int side, int position = -1)
  {
    if (position < 0 || position > _minion[side].size())
      _minion[side].push_back(m);
    else
      _minion[side].insert(_minion[side].begin() + position,m);
  }
  void destroy_minion(int position,int side)
  {
    if (position < 0 || position >= _minion[side].size())
      return;
    if (_minion[side][position] != NULL)
      delete _minion[side][position];
    _minion[side].erase(_minion[side].begin() + position);
  }
  static bool attack(Character *a, Character *b)
  {
    if (!a->canAttack())
      return false;

    a->attacking(b);
    b->attacked(a);
    return true;
};

#endif
