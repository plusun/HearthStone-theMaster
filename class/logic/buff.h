#ifndef _CLASS_BUFF_
#define _CLASS_BUFF_

#include "basic.h"

class Buff
{
public:
  bool _taunt;
  bool _charge;
  int _spell_dmg;
  bool _windfury;
  bool _stealth;
  int _atk;
  int _hp;
  bool _oneturn;
  bool _shield;
  Buff():
    _taunt(false), _charge(false),
    _spell_dmg(0), _windfury(false),
    _stealth(false), _atk(0), _hp(0),
    _oneturn(false),_shield(false)
  {
  }
};

#endif
