#include "basic.h"
#include "weapon.h"

class Character
{
public:
	Value _health, _max_health;
	Value _attack;

  Character(Value h,  Value a,):
    _health(h), _attack(a), _max_health(h)
  {
  }
};

class Hero: public Character
{
public:
	Hero(Value h):
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
	Value _ori_health;
	Value _ori_attack;
	void _attack();
	Minion(){};
};
