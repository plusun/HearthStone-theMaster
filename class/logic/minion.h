#ifndef _CLASS_MINION_
#define _CLASS_MINION_

#include "character.h"
#include "spell.h"

class Spell001 : public Single_spell
{
public:
  void cast();
};

class Spell002 : public Single_spell
{
public:
  void cast();
};

class Wisp : public Minion
{
public:
  Wisp():
    Minion(none, 1, 1)
  {
    battlecry();
  }
  void battlecry(){};
  void effect(){};
  void deathrattle(){};
};

class Abusive_sergeant : public Minion
{
public:
  Abusive_sergeant():
    Minion(none, 1, 2)
  {
    battlecry();
  }
  void battlecry()
  {
    Spell001 _spell;
    _spell.cast();
  }
  void effect(){};
  void deathrattle(){};
};

class Argent_squire : public Minion
{
public:
  Argent_squire():
    Minion(none, 1, 1)
  {
    battlecry();
  }
  void battlecry()
  {
    Buff _buff;
    _buff._shield = true;
    this->_buff.push_back(_buff);
  }
  void effect(){};
  void deathrattle(){};
};

class Hungry_crab : public Minion
{
public:
  Hungry_crab():
    Minion(beast, 2, 1)
  {
    battlecry();
  }
  void battlecry()
  {
    Spell002 _spell;
    _spell.cast();
  }
  void effect(){};
  void deathrattle(){};
};



// void Spell001::cast()
// {
//   //TODO
//   _select_target = NULL;
//   Buff _buff;
//   _buff._oneturn = true;
//   _buff._atk = 2;
//   _select_target->_buff.push_back(_buff);
// };

// void Spell002::cast()
// {
//   //TODO
//   if (_select_target.race != beast)
//     _select_target = NULL;
//   Buff _buff;
//   _buff._atk = 2;
//   _buff._hp = 2;
//   this->_buff.push_back(_buff);
// };
#endif
