#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "basic.h"
#include "weapon.h"
#include "cocos2d.h"

USING_NS_CC;


class Character
{
private:
  bool _immune, _tired;
  int _health, _max_health, _frozen;
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
  void deFrozen();
  void tired(bool);
  bool tired();
  bool immune();
  void immune(int new_immune);
  virtual bool canAttack();
  virtual void attacking(Character *c);
  virtual void attacked(Character *c);
  virtual void damaged(int);
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
  void damaged(int);
  void destroyWeapon();
};

class Minion: public Character
{
private:
  Race _race;
  int _ori_health;
  int _ori_attack;
  bool _new_minion;
public:
  Minion(Race r, int h, int a, int mh = -1, int oh = -1, int oa = -1, bool nm = true);
  int originalHealth();
  void originalHealth(int);
  int originalAttack();
  void originalAttack(int);
  bool newMinion();
  void newMinion(bool);
  bool canAttack();
  Sprite * Sprite_card;
};

#endif
