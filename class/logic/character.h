#ifndef _CLASS_CHARACTER_
#define _CLASS_CHARACTER_

#include "stdlib.h"
#include "basic.h"
#include "weapon.h"
#include "buff.h"

class Character
{
private:
  bool _frozen, _immune;
  int _health, _max_health;
protected:
  int _attack;
public:
  Character(int h,  int a, int mh = -1, bool f = false, bool i = false):
    _health(h), _attack(a), _max_health(mh),  _frozen(f), _immune(i)
  {
    if (_max_health < 0)
      _max_health = h;
  }
  int health()
  {
    return _health;
  }
  void health(int new_health)
  {
    _health = new_health;
  }
  int maxHealth()
  {
    return _max_health;
  }
  void maxHealth(int new_max_health)
  {
    _max_health = new_max_health;
  }
  virtual int attack()
  {
    return _attack;
  }
  void attack(int new_attack)
  {
    _attack = new_attack;
  }
  bool frozen()
  {
    return _frozen;
  }
  void frozen(bool new_frozen)
  {
    _frozen = new_frozen;
  }
  bool immune()
  {
    return _immune;
  }
  void immune(int new_immune)
  {
    _immune = new_immune;
  }
  bool canAttack()
  {
    return attack() > 0;
  }
};

class Hero: public Character
{
private:
  int _armor;
  Weapon *_weapon;
public:
  Hero(int h):
    Character(h, 0)
  {
    _armor = 0;
    _weapon = NULL;
  }
  ~Hero()
  {
    if (_weapon != NULL)
      delete _weapon;
  }

  int armor()
  {
    return _armor;
  }
  void armor(int new_armor)
  {
    _armor = new_armor;
  }

  int attack()
  {
    if (_weapon == NULL)
      return _attack;
    else
      return _attack + _weapon->attack();
  }
  Weapon *weapon()
  {
    return _weapon;
  }
  void weapon(Weapon *new_weapon)
  {
    if (new_weapon != NULL &&
	new_weapon->durable() > 0 &&
	new_weapon->attack() > 0)
      {
	if (_weapon != NULL)
	  delete _weapon;
	_weapon = new_weapon;
      }
  }
};

class Minion: public Character
{
private:
  Race _race;
  int _ori_health;
  int _ori_attack;
public:
  Minion(Race r, int h, int a, int mh = -1, int oh = -1, int oa = -1):
    Character(h, a, mh), _race(r), _ori_health(oh), _ori_attack(oa)
  {
    if (_ori_health < 0)
      _ori_health = maxHealth();
    if (_ori_attack < 0)
      _ori_attack = attack();
  }
  vector<Buff> _buff;
  void _attack();
};

#endif
