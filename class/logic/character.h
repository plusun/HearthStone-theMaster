#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "basic.h"
#include "weapon.h"
#include "cocos2d.h"
#include "buff.h"
#include <string>
USING_NS_CC;

#define MAXHERONO 9

class Character
{
private:
  bool _immune;
  int _health, _max_health, _frozen;
protected:
  int _attack;
  int _tired;
public:
  int no;
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
  virtual bool tired();
  bool immune();
  void immune(int new_immune);
  virtual bool canAttack();
  virtual void attacking(Character *c);
  virtual void attacked(Character *c);
  virtual void damaged(int);
  Sprite * Sprite_card;
  Sprite * Type;
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
  // new minion means that it cannot attack at first round
  bool _new_minion;
public:
  Buff buff;
  Minion(Race r, int h, int a, int mh = -1, int oh = -1, int oa = -1, bool nm = true, Buff b = Buff());
  int originalHealth();
  void originalHealth(int);
  int originalAttack();
  void originalAttack(int);
  bool newMinion();
  void newMinion(bool);
  void damaged(int);
  bool tired();
  bool canAttack();
  Race race();
};

std::string CharacterToFilename(Character *);

#endif
