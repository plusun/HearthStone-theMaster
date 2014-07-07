#include "character.h"

  Character::Character(int h,  int a, int mh, bool f, bool i):
    _health(h), _attack(a), _max_health(mh),  _frozen(f), _immune(i)
  {
    if (_max_health < 0)
      _max_health = h;
  }
  int Character::health()
  {
    return _health;
  }
  void Character::health(int new_health)
  {
    _health = new_health;
  }
  int Character::maxHealth()
  {
    return _max_health;
  }
  void Character::maxHealth(int new_max_health)
  {
    _max_health = new_max_health;
  }
  int Character::attack()
  {
    return _attack;
  }
  void Character::attacking(Character *c)
  {
    health(health() - c->attack());
  }
  void Character::attacked(Character *who)
  {
    health(health() - who->attack());
  }
  void Character::attack(int new_attack)
  {
    _attack = new_attack;
  }
  bool Character::frozen()
  {
    return _frozen;
  }
  void Character::frozen(bool new_frozen)
  {
    _frozen = new_frozen;
  }
  bool Character::immune()
  {
    return _immune;
  }
  void Character::immune(int new_immune)
  {
    _immune = new_immune;
  }
  bool Character::canAttack()
  {
    return attack() > 0;
  }

  Hero::Hero(int h):
    Character(h, 0)
  {
    _armor = 0;
    _weapon = NULL;
  }
  Hero::~Hero()
  {
    if (_weapon != NULL)
      delete _weapon;
  }

  int Hero::armor()
  {
    return _armor;
  }
  void Hero::armor(int new_armor)
  {
    _armor = new_armor;
  }

  int Hero::attack()
  {
    if (_weapon == NULL)
      return _attack;
    else
      return _attack + _weapon->attack();
  }
  Weapon *Hero::weapon()
  {
    return _weapon;
  }
  void Hero::destroyWeapon()
  {
    if (_weapon != NULL)
      delete _weapon;
    _weapon = NULL;
  }
  void Hero::attacking(Character *who)
  {
	health(health() - who->attack());
    if (weapon() != NULL)
      {
	weapon()->durable(weapon()->durable() - 1);
	if (weapon()->durable() <= 0)
	  destroyWeapon();
      }
  }
  void Hero::weapon(Weapon *new_weapon)
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

  Minion::Minion(Race r, int h, int a, int mh, int oh, int oa):
    Character(h, a, mh), _race(r), _ori_health(oh), _ori_attack(oa)
  {
    if (_ori_health < 0)
      _ori_health = maxHealth();
    if (_ori_attack < 0)
      _ori_attack = attack();
  }