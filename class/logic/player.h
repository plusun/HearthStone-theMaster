#include "basic.h"
#include "character.h"
#include "mana.h"
#include "battlefield.h"
#include "handcard.h"

class Player
{
public:
	Hero _hero;
	Deck _deck;
	Battlefield _battlefield
	Handcard _handcard;
	Mana _mana;
	Secret_slot _secret;
	bool is_host;
	bool is_first;
public:
	Player();
	void init();
	void turn();
}

void Player::init()
{
	if (is_first)
	{
		for (int i = 0; i < 3; i++)
			_handcard.draw_card(_deck.give_card());
		_mana.inc_max_mana(1);
		_mana.inc_cur_mana(1);
	}
	else
	{
		for (int i = 0; i < 4; i++)
			_handcard.draw_card(_deck.give_card());
	}

};