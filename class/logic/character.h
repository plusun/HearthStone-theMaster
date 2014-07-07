#ifndef _CHARACTER_H_
#define _CHARACTER_H_

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
  Character(int h,  int a, int mh = -1, bool f = false, bool i = false);
  int health();
  void health(int new_health);
  int maxHealth();
  void maxHealth(int new_max_health);
  virtual int attack();
  void attack(int new_attack);
  bool frozen();
  void frozen(bool new_frozen);
  bool immune();
  void immune(int new_immune);
  bool canAttack();
  virtual void attacking(Character *c);
  virtual void attacked(Character *c);
};

class Hero: public Character
{
private:
  int _armor;
  Weapon *_weapon;
public:
  Hero(int h);
  ~Hero();
  int armor();
  void armor(int new_armor);
  int attack();
  Weapon *weapon();
  void weapon(Weapon *new_weapon);
  void attacking(Character *);
  void destroyWeapon();
};

class Minion: public Character
{
private:
  Race _race;
  int _ori_health;
  int _ori_attack;
public:
  Minion(Race r, int h, int a, int mh = -1, int oh = -1, int oa = -1);
};

#endif