#include "basic.h"
#include "weapon.h"

class Character
{
private:
  bool _frozen, _immune;
  Value _health, _max_health;
protected:
  Value _attack;
public:
  Character(Value h,  Value a, bool r = true, bool f = false, bool i = false):
    _health(h), _attack(a), _round(r), _frozen(f), _immune(i)
  {
  }
  Value health()
  {
    return _health;
  }
  void health(Value new_health)
  {
    _health = new_health;
  }
  Value maxHealth()
  {
    return _max_health;
  }
  void maxHealth(new_max_health)
  {
    _max_health = new_max_health;
  }
  virtual Value attack()
  {
    return _attack;
  }
  void attack(Value new_attack)
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
  void immune(new_immune)
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
  Value _armor;
  Weapon *_weapon;
public:
  Hero(Value h):
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

  Value armor()
  {
    return _armor;
  }
  void armor(Value new_armor)
  {
    _armor = new_armor;
  }

  Value attack()
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

enum Race {BEAST};

class Minion: public Character
{
private:
public:
};
