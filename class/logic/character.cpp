#include "character.h"

Character::Character(int h,  int a, int mh, bool f, bool i):
  _health(h), _attack(a), _max_health(mh),  _frozen(f), _immune(i), _tired(false)
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
  damaged(c->attack());
}
void Character::attacked(Character *who)
{
  damaged(who->attack());
}
void Character::damaged(int damage)
{
  health(health() - damage);
}
void Character::attack(int new_attack)
{
  _attack = new_attack;
}
bool Character::frozen()
{
  return _frozen > 0;
}
void Character::frozen(bool new_frozen)
{
  if (new_frozen)
    _frozen = 2;
  else
    _frozen = 0;
}
void Character::deFrozen()
{
  if (_frozen > 0)
    --_frozen;
}
bool Character::tired()
{
  return _tired;
}
void Character::tired(bool new_tired)
{
  _tired = new_tired;
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
  return !tired() && !frozen() && attack() > 0;
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
void Hero::damaged(int damage)
{
  if (damage < 0)
    health(health() - damage);
  else
    {
      int dearmor = damage < armor() ? damage : armor();
      armor(armor() - dearmor);
      health(health() - (damage - dearmor));
    }
}
void Hero::attacking(Character *who)
{
  damaged(who->attack());
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

Minion::Minion(Race r, int h, int a, int mh, int oh, int oa, bool nm, Buff b):
  Character(h, a, mh), _race(r), _ori_health(oh), _ori_attack(oa), _new_minion(nm),
  buff(b)
{
  if (_ori_health < 0)
    _ori_health = maxHealth();
  if (_ori_attack < 0)
    _ori_attack = attack();
}

int Minion::originalHealth()
{
  return _ori_health;
}
void Minion::originalHealth(int oh)
{
  _ori_health = oh;
}

int Minion::originalAttack()
{
  return _ori_attack;
}
void Minion::originalAttack(int oa)
{
  _ori_attack = oa;
}

bool Minion::newMinion()
{
  return _new_minion;
}
void Minion::newMinion(bool nm)
{
  _new_minion = nm;
}

void Minion::damaged(int damage)
{
	int debuf = damage < buff._hp ? damage : buff._hp;
	damage -= debuf;
	buff._hp -= debuf;
	health(health() - damage);
}

bool Minion::canAttack()
{
  return !newMinion() && !tired() && !frozen() && attack() > 0;
}
Race race()
{
  return _race;
}
