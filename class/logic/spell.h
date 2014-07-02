#include "basic.h"

target enum{ally,all_ally,enemy,all_enemy};

class spell
{
	void cast() = 0;
};

class single_spell : public spell
{
	object1 _select_target;
	void effect1();				//buff,dmg,heal
	bool do_effect2();
	void effect2();				//call imm-use_spell?
};

class aoe_spell : public spell
{
	target _target;
	void effect1();				//buff,dmg,heal
};

class adjacent_spell : public spell
{
	object1 _select_target;
	object1 _adjacent_target[2];
	void effect1();
	void effect2();
};

class two_target_spell : public spell
{
	object1 _target[2];
	void effect();
};

class imm-use_spell : public spell
{
	vector<object1> _target;			//should be cal in cast()
};