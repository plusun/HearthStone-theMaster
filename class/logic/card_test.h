#include "card.h"
#include "spell.h"
#include "minion_test.h"

class Wisp_card : public Minion_card
{
public:
	Wisp_card(1,NULL);
}

Wisp_card::cast()
{
	_minion = new Wisp;

}

class Murloc_raider_card : public Minion_card
{
public:
	Murloc_raider(1,NULL);
}

Murloc_raider_card::cast()
{
	_minion = new Murloc_raid;
}

class Bloodfen_raptor_card 