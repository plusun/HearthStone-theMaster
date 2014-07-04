#include "basic.h"
#include "character_test.h"

#define SIDE 2

class Battlefield
{
public:
  vector<Minion *> _minion[SIDE];
  Hero *_hero[SIDE];
  Battlefield(Hero *one, Hero *another)
  {
    _hero[0] = one;
    _hero[1] = another;
  }
  ~Battlefield()
  {
<<<<<<< HEAD
    for (vector<Minion *>::iterator itr = _minion.begin();
	 itr != _minion.end();
	 ++itr)
      if (*itr != NULL)
	delete *itr;
    for (vector<Hero *>::iterator itr = _hero.begin();
	 itr != _hero.end();
	 ++itr)
      if (*itr != NULL)
	delete *itr;
  }
  void summon_minion(Minion* m, int position = -1)
=======
    for (int i = 0; i < SIDE; ++i)
      for (vector<Mionion *>::iterator itr = _minion[i].begin();
	   itr != _minion[i].end();
	   ++itr)
	if (*itr != NULL)
	  delete *itr;
    for (int i = 0; i < SIDE; ++i)
      if (_hero[i] != NULL)
	delete _hero[i];
  }
  void summon_minion(minion* m, int side, int position = -1)
>>>>>>> 5a57dd7eeaaa921f766c115eeb9eceec34cece55
  {
    if (position < 0 || position > _minion[side].size())
      _minion[side].push_back(m);
    else
<<<<<<< HEAD
      _minion.insert(_minion.begin() + position,m);
=======
      _minion[side].insert(_minion[side].begin() + position);
>>>>>>> 5a57dd7eeaaa921f766c115eeb9eceec34cece55
  }
  void destroy_minion(int position)
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
  }
};
