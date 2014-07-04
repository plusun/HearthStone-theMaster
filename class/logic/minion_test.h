#include "character.h"

class Wisp : public Minion
{
public:
	Wisp():_race(none),_ori_attack(1),_attack(1),_ori_health(1),_max_health(1),_health(1){};
};

class Murloc_raider : public Minion
{
public:
	Murloc_raider:_race(murloc),_ori_attack(2),_attack(2),_ori_health(1),_max_health(1),_health(1){};
};

class Bloodfen_raptor : public Minion
{
public:
	Bloodfen_raptor:_race(beast),_ori_attack(3),_attack(3),_ori_health(2),_max_health(2),_health(2){};
};

class River_crocolisk : public Minion
{
public:
	River_crocolisk():_race(beast),_ori_attack(2),_attack(2),_ori_health(3),_max_health(3),_health(3){};
};

class Magma_Rager : public Minion
{
public:
	Magma_Rager():_race(none),_ori_attack(5),_attack(5),_ori_health(1),_max_health(1),_health(1){};
};

class Chiliwind_yeti : public Minion
{
public:
	Chiliwind_yeti():_race(none),_ori_attack(4),_attack(4),_ori_health(5),_max_health(5),_health(5){};
};

class Oasis_snapjaw : public Minion
{
public:
	Oasis_snapjaw():_race(beast),_ori_attack(2),_attack(2),_ori_health(7),_max_health(7),_health(7){};
};

class Boulderfist_ogre : public Minion
{
public:
	Boulderfist_ogre():_race(none),_ori_attack(6),_attack(6),_ori_health(7),_max_health(7),_health(7){};
};

class Core_hound : public Minion
{
public:
	Core_hound():_race(beast),_ori_attack(9),_attack(9),_ori_health(5),_max_health(5),_health(5){};
};

class War_golem : public Minion
{
public:
	War_golem():_race(none),_ori_attack(7),_attack(7),_ori_health(7),_max_health(7),_health(7){};
};
