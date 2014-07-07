#include "card.h"
#include "minion_test.h"

class Wisp_card : public MinionCard
{
public:
	Wisp_card(1,NULL);
}

Wisp_card::cast()
{
	_minion = new Wisp;

}


class Murloc_raider_card : public MinionCard
{
public:
	Murloc_raider(1,NULL);
}

Murloc_raider_card::cast()
{
	_minion = new Murloc_raid;
}


class Bloodfen_raptor_card : public MinionCard
{
public:
	Bloodfen_raptor(2,NULL);
}

Bloodfen_raptor_card::cast()
{
	_minion = new Bloodfen_raptor;
}


class River_crocolisk_card : public MinionCard
{
public:
	River_crocolisk(2,NULL);
}

River_crocolisk_card::cast()
{
	_minion = new River_crocolisk;
}


class Magma_Rager_card : public MinionCard
{
public:
	Magma_Rager(3,NULL);
}

Magma_Rager_card::cast()
{
	_minion = new Magma_Rager;
}


class Chiliwind_yeti_card : public MinionCard
{
public:
	Chiliwind_yeti(4,NULL);
}

Chiliwind_yeti_card::cast()
{
	_minion = new Chiliwind_yeti;
}


class Oasis_snapjaw_card : public MinionCard
{
public:
	Oasis_snapjaw(4,NULL);
}

Oasis_snapjaw_card::cast()
{
	_minion = new Oasis_snapjaw;
}


class Boulderfist_ogre_card : public MinionCard
{
public:
	Boulderfist_ogre(6,NULL);
}

Boulderfist_ogre_card::cast()
{
	_minion = new Boulderfist_ogre;
}


class Core_hound_card : public MinionCard
{
public:
	Core_hound(7,NULL);
}

Core_hound_card::cast()
{
	_minion = new Core_hound;
}


class War_golem_card : public MinionCard
{
public:
	War_golem(7,NULL);
}

War_golem_card::cast()
{
	_minion = new War_golem;
}