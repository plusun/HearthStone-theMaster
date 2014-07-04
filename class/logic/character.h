#include "basic.h"
#include "weapon.h"

class Character
{
private:
  bool _frozen, _immune;
  int _health, _max_health;
protected:
  int _attack;
public:
  Character(int h,  int a, int m = -1, bool f = false, bool i = false):
    _health(h), _attack(a), _max_health(m), _frozen(f), _immune(i)
  {
    if (_max_health < 0)
      _max_health = _health;
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
  void maxHealth(new_max_health)
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
  void immune(new_immune)
  {
    _immune = new_immune;
  }
  virtual bool canAttack()
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

enum Race {none=0, beast, murloc, pirate, dragon, demon, totem};

class Minion: public Character
{
private:
  Race _race;
  int _ori_health;
  int _ori_attack;
  int lifespan;
public:
  Minion(Race r, int h, int a, int m = -1, int oh = -1, int oa = -1):
    Character(h, a, m), _race(r), _ori_health(oh), _ori_attack(oa), lifespan(0)
  {
    if (_ori_health < 0)
      _ori_health = maxHealth();
    if (_ori_attack < 0)
      _ori_attack = attack();
  }
  vector<Buff> _buff;
  Race race()
  {
    return _race;
  }
  int originalHealth()
  {
    return _ori_health;
  }
  int originalAttack()
  {
    return _ori_attack();
  }
  bool canAttack()
  {
    return lifespan > 0 && attack() > 0;
  }
};
