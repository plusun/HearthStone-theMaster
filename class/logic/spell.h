#ifndef _CLASS_SPELL_
#define _CLASS_SPELL_

#include "basic.h"

enum target {ally,all_ally,enemy,all_enemy};

class Spell
{
public:
  void cast();
};

class Single_spell : public Spell
{
public:
  Character *_select_target;
  void effect1();				//buff,dmg,heal
  bool do_effect2();
  void effect2();				//call imm-use_spell?
  
};

class Aoe_spell : public Spell
{
  target _target;
  void effect1();				//buff,dmg,heal
};

class Adjacent_spell : public Spell
{
  Character _select_target;
  Character _adjacent_target[2];
  void effect1();
  void effect2();
};

class Two_target_spell : public Spell
{
  Character _target[2];
  void effect();
};

class Immuse_spell : public Spell
{
  vector<Character> _target;			//should be cal in cast()
};

#endif
