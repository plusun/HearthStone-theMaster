#ifndef _SPELL_
#define _SPELL_

#include "basic.h"
#include "character.h"
#include "battlefield.h"

#define DEATHDMG 9999

enum SpellType
  {
    BuffTaunt, BuffCharge, BuffSpellDmg,
    BuffWindfurry, BuffStealth, BuffAtk,
    BuffHp, BuffOneturn, BuffShield,
    DMG, HEAL, CLEAR, IMMUNE, FROZEN, SILENCE
  };
enum Target
  {
    SPECIFIC, ALL,
    AllHero, AllMinion,
    AllEnemy, AllEnemyHero,
    AllEnemyMinion
  };

class Spell
{
public:
  Spell(Target t, SpellType st, int v, Battlefield *b, int s):
    target(t), type(st), value(v), bf(b), side(s)
  {
  }
  vector<Hero *> heroes;
  vector<Minion *> minions;
  Target target;
  SpellType type;
  int value;
  Battlefield *bf;
  int side;

  virtual bool use(Hero *heroTarget = NULL, Minion *minionTarget = NULL)
  {
    int MAXHP = 10086;
    int number = 0;
    switch (target)
      {
      case SPECIFIC:
	heroes.clear();
	minions.clear();
	if (heroTarget != NULL)
	  heroes.push_back(heroTarget);
	if (minionTarget != NULL)
	  minions.push_back(minionTarget);
	number = heroes.size() + minions.size();
	if (number != 1)
	  return false;
	break;
      case ALL:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  {
	    heroes.push_back(bf->_hero[i]);
	    for (int j = 0; j < bf->_minion[i].size(); ++j)
	      minions.push_back(bf->_minion[i][j]);
	  }
	break;
      case AllHero:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  {
	    heroes.push_back(bf->_hero[i]);
	  }
	break;
      case AllMinion:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  {
	    for (int j = 0; j < bf->_minion[i].size(); ++j)
	      minions.push_back(bf->_minion[i][j]);
	  }
	break;
      case AllEnemy:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  if (i != side)
	    {
	      heroes.push_back(bf->_hero[i]);
	      for (int j = 0; j < bf->_minion[i].size(); ++j)
		minions.push_back(bf->_minion[i][j]);
	    }
	break;
      case AllEnemyHero:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  if (i != side)
	    {
	      heroes.push_back(bf->_hero[i]);
	    }
	break;
      case AllEnemyMinion:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  if (i != side)
	    {
	      for (int j = 0; j < bf->_minion[i].size(); ++j)
		minions.push_back(bf->_minion[i][j]);
	    }
	break;
      default:
	break;
      }
    switch (type)
      {
      case BuffTaunt:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._taunt = true;
	break;
      case BuffCharge:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._charge = true;
	break;
      case BuffSpellDmg:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._spell_dmg += value;
	break;
      case BuffWindfurry:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._windfury = true;
	break;
      case BuffStealth:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._stealth = true;
	break;
      case BuffAtk:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._atk += value;
	break;
      case BuffHp:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._hp += value;	
	break;
      case BuffOneturn:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._oneturn = true;
	break;
      case BuffShield:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->buff._shield = true;
	break;
      case DMG:
	for (int i = 0; i < heroes.size(); ++i)
	  heroes[i]->damaged(value);
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->damaged(value);
	break;
      case HEAL:
	for (int i = 0; i < heroes.size(); ++i)
	  heroes[i]->damaged(-value);
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->damaged(-value);
	break;
      case IMMUNE:
	for (int i = 0; i < heroes.size(); ++i)
	  heroes[i]->immune(true);
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->immune(true);
	break;
      case FROZEN:
	for (int i = 0; i < heroes.size(); ++i)
	  heroes[i]->frozen(true);
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->frozen(true);
	break;
      case CLEAR:
	for (int i = 0; i < minions.size(); ++i)
	  minions[i]->damaged(MAXHP);
	break;
      case SILENCE:
	for (int i = 0; i < minions.size(); ++i)
	  {
	    minions[i]->buff = Buff();
	    minions[i]->frozen(false);
	    minions[i]->immune(false);
	  }
	break;
      default:
	break;
      }
    
    return true;
  }
};

class Flamestrike: public Spell
{
public:
  Flamestrike(Battlefield *bf, int side):
    Spell(AllEnemyMinion, DMG, 4, bf, side) {}
};

class Consecration: public Spell
{
public:
  Consecration(Battlefield *bf, int side):
    Spell(AllEnemyMinion, DMG, 2, bf, side) {}
};

class ArcaneExplosion: public Spell
{
public:
  ArcaneExplosion(Battlefield *bf, int side):
    Spell(AllEnemyMinion, DMG, 1, bf, side) {}
};

class Fireball: public Spell
{
public:
  Fireball(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 6, bf, side) {}
};

class Moonfire: public Spell
{
public:
  Moonfire(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 1, bf, side) {}
};

class Starfall: public Spell
{
public:
  Starfall(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 5, bf, side) {}
};

class Pyroblast: public Spell
{
public:
  Pyroblast(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 10, bf, side) {}
};

class HolyLight: public Spell
{
public:
  HolyLight(Battlefield *bf, int side):
    Spell(SPECIFIC, HEAL, 6, bf, side) {}
};

class Assassinate: public Spell
{
public:
  Assassinate(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, DEATHDMG, bf, side) {}
};

class TwistingNether: public Spell
{
public:
  TwistingNether(Battlefield *bf, int side):
    Spell(AllEnemyMinion, DMG, DEATHDMG, bf, side) {}
};

class Hellfire: public Spell
{
public:
  Hellfire(Battlefield *bf, int side):
    Spell(ALL, DMG, 3, bf, side) {}
};

class ShadowBolt: public Spell
{
public:
  ShadowBolt(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 4, bf, side) {}
};

class ArcaneShot: public Spell
{
public:
  ArcaneShot(Battlefield *bf, int side):
    Spell(SPECIFIC, DMG, 2, bf, side) {}
};

class CircleOfHealing: public Spell
{
public:
  CircleOfHealing(Battlefield *bf, int side):
    Spell(AllMinion, HEAL, 4, bf, side) {}
};

#endif
