#ifndef __BATTLEFIELD__
#define __BATTLEFIELD__

#include "basic.h"
#include "character.h"

#define SIDE 2
#define MAXMINIONB 10

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
  bool summon_minion(Minion* m, int side , int position = -1)
  {
    if (_minion[side].size() > MAXMINIONB)
      return false;
    if (position < 0 || position > _minion[side].size())
      _minion[side].push_back(m);
    else
      _minion[side].insert(_minion[side].begin() + position,m);
    return true;
  }
  void destroy_minion(int side, int position)
  {
    if (position < 0 || position >= _minion[side].size())
      return;
    if (_minion[side][position] != NULL)
      delete _minion[side][position];
    _minion[side].erase(_minion[side].begin() + position);
  }
  bool canBeAttacked(Character *b)
  {
    int side = -1;
    bool hero = false;
    for (int i = 0; i < SIDE; ++i)
      {
	if (_hero[i] == b)
	  {
	    side = i;
	    hero = true;
	    break;
	  }
	for (int j = 0; j < _minion[i].size(); ++j)
	  if (_minion[i][j] == b)
	    {
	      side = i;
	      break;
	    }
	if (side >= 0)
	  break;
      }
    if (side < 0)
      return false;
    if (!hero && ((Minion *)b)->buff._taunt)
      return true;
    for (int i = 0; i < _minion[side].size(); ++i)
      if (_minion[side][i]->buff._taunt)
	return false;
    return true;
  }
  bool attack(Character *a, Character *b)
  {
    if (!a->canAttack())
      return false;
    if (!canBeAttacked(b))
      return false;
    a->attacking(b);
    b->attacked(a);
    a->tired(true);
    return true;
  }
  void checkAndDead()
  {
    for (int side = 0; side < SIDE; ++side)
      for (int i = 0; i < _minion[side].size(); ++i)
	if (_minion[side][i]->health() <= 0)
	  destroy_minion(side, i);
  }
  int checkwin()
  {
	  int n = 0;
	  if (_hero[0]->health() <= 0)
		  n += 1;
	  if (_hero[1]->health() <= 0)
		  n += 2;
	  return n;
  }
  void startSide(int side)
  {
    for (int i = 0; i < _minion[side].size(); ++i)
      {
	_minion[side][i]->deFrozen();
	_minion[side][i]->newMinion(false);
      }
  }
  void overSide(int side)
  {
    for (int i = 0; i < _minion[side].size(); ++i)
      _minion[side][i]->tired(false);
  }
};

#endif
