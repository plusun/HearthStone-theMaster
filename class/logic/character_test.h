#ifndef __CHARATER_TEST_H__
#define __CHARATER_TEST_H__

#include "basic.h"

class Character
{
public:
	int _health, _max_health;
	int _attack;
	Character(){};
};

class Hero: public Character
{
public:
	Hero(int h):
    Character()
	{
	}
	~Hero()
	{
	}
};

class Minion: public Character
{
public:
	Race _race;
	int _ori_health;
	int _ori_attack;
	void _attack();
	Minion(){};
};

#endif;