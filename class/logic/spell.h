#include "basic.h"

target enum{ally,all_ally,enemy,all_enemy};

class Spell
{
	void cast() = 0;
};

class Single_spell : public Spell
{
	Character _select_target;
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

class Imm-use_spell : public Spell
{
	vector<Character> _target;			//should be cal in cast()
};