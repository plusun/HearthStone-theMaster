#include "basic.h"

class Character
{
public:
	int _health, _max_health;
	int _attack;

  Character(int h,  int a,):
    _health(h), _attack(a), _max_health(h)
  {
  }
};

class Hero: public Character
{
public:
	Hero(int h):
    Character(h, 0)
	{
	}
	~Hero()
	{
	}
};

enum Race {none=0, beast, murloc, pirate, dragon, demon, totem};

class Minion: public Character
{
public:
	Race _race;
	int _ori_health;
	int _ori_attack;
	void _attack();
	Minion(){};
};
