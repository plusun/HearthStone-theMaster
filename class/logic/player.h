#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "basic.h"
#include "character_test.h"
#include "mana.h"
#include "battlefield.h"
#include "handcard.h"
#include "deck.h"

#define maxhp 30


class Sustainable_effect
{
public:
	checkpoint _time;
	Character _targe;
	void effect();
};

class Player
{
public:
	deck _deck;
	Battlefield _battlefield;
	Handcard _handcard;
	Mana _mana;
	//Secret_slot _secret;
	bool is_host;
	bool is_first;
	Player* oppoent;
public:
	Player();

	void init();
	void turn();
};


#endif