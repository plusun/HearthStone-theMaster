#include "charater.h"
#include "spell.h"

class Wisp : public Minion
{
public:
	Wisp():_race(none),_ori_attack(1),_attack(1),_ori_health(1),_max_health(1),_health(1){battlecry()};
	void battlecry(){};
	void effect(){};
	void deathrattle(){};
};

class Abusive_sergeant : public Minion
{
public:
	Abusive_sergeant:_race(none),_ori_attack(2),_attack(2),_ori_health(1),_max_health(1),_health(1){battlecry()};
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
	Argent_squire:_race(none),_ori_attack(1),_attack(1),_ori_health(1),_max_health(1),_health(1){battlecry()};
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
	Hungry_crab():_race(beast),_ori_attack(1),_attack(1),_ori_health(2),_max_health(2),_health(2){battlecry()};
	void battlecry()
	{
		Spell002 _spell;
		_spell.cast();
	}
	void effect(){};
	void deathrattle(){};
}


class Spell001 : public Single_spell
{
	
};

void Spell001::cast()
{
	//TODO
	_select_target = ;
	Buff _buff;
	_buff._oneturn = true;
	_buff._atk = 2;
	_select_target._buff.push_back(_buff);
};

class Spell002 : public Single_spell
{
	
};

void Spell002::cast()
{
	//TODO
	if (_select_target.race != beast)
		_select_target = ;
	Buff _buff;
	_buff._atk = 2;
	_buff._hp = 2;
	this->_buff.push_back(_buff);
};