#ifndef _SPELL_
#define _SPELL_

#include "basic.h"
#include "character.h"

enum SpellType
  {
    BuffTaunt, BuffCharge, BuffSpellDmg,
    BuffWindfurry, BuffStealth, BuffAtk,
    BuffHp, BuffOneturn, BuffShield,
    DMG, HEAL, CLEAR
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
  Spell(Target t, SpellType st, int v, Player *p):
    target(t), type(st), value(v), pl(p)
  {
  }
  vector<Hero *> heroes;
  vector<Minion *> minions;
  Target target;
  SpellType type;
  int value;
  Player *pl;
  virtual use()
  {
    Battlefield *bf = player->_battlefield;
    switch (target)
      {
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
	  if (i != pl->side)
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
	  if (i != pl->side)
	    {
	      heroes.push_back(bf->_hero[i]);
	    }
	break;
      case AllEnemyMinion:
	heroes.clear();
	minions.clear();
	for (int i = 0; i < SIDE; ++i)
	  if (i != pl->side)
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
	break;
      case BuffCharge:
	break;
      case BuffSpellDmg:
	break;
      case BuffWindfurry:
	break;
      case BuffStealth:
	break;
      case BuffAtk:
	break;
      case BuffHp:
	break;
      case BuffOneturn:
	break;
      case BuffShield:
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
      case CLEAR:
	break;
      default:
	break;
      }
  }
};

class Flamestrike: Spell
{
public:
  Flamestrike(Player *p):
    Spell(AllEnemyMinion, DMG, 4, p) {}
};

#endif
