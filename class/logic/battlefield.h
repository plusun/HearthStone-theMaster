#include "basic.h"
#include "character.h"

class Battlefield
{
public:
  vector<Minion *> _minion;
  vector<Hero *> _hero;
  Battlefield()
  {
    _minion.clear();
    _hero.clear();
  }
  ~Battlefield()
  {
    for (vector<Mionion *>::iterator itr = _minion.begin();
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
  void summon_minion(minion* m, int position = -1,)
  {
    if (position < 0 || position > _minion.size())
      _minion.push_back(m);
    else
      _minion.insert(_minion.begin() + position);
  }
  void destroy_minion(int position)
  {
    if (position < 0 || position >= _minion.size())
      return;
    if (_minion[position] != NULL)
      delete _minion[position];
    _minion.erase(_minion.begin() + position);
  }
}
