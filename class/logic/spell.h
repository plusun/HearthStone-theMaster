#ifndef _SPELL_
#define _SPELL_

#include "basic.h"
#include "character.h"
#include "player.h"

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

  virtual void use()
  {
    Battlefield *bf = pl->_battlefield;
    int MAXHP = 10086;
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
    bf->checkAndDead();
  }
};

class Flamestrike: Spell
{
public:
  Flamestrike(Player *p):
    Spell(AllEnemyMinion, DMG, 4, p) {}
};

#endif
