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

Player::Player()
{
	is_host = false;
	is_first = false;
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
	//opponent = receive_from_server();
};

void Player::turn()
{
	//preparation
	if ( _mana._max_mana < 10 )					//max mana++ & restore mana
		_mana.inc_max_mana();
	_mana.restore_mana();

	//player's choice


	//TODO: use card

	{

		//_mana.cost_mana(card.cost);
		//TODO: summon minion
		{

		}

		//TODO: cast spell
		{

		}

		//TODO: use weapon
		{


		}

	}

	//TODO: hero ability
	{

	}

	//TODO: minion attack
	{

	}

	//TODO: click 'end turn' button
	return;
}

#endif