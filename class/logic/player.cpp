#include "player.h"


Player::Player(deck *d, Battlefield *b, bool f = true):
  _deck(d), _battlefield(b), is_first(f)
{
}

bool draw()
{
  int n = _deck->give_card();
  if (!_handcard.full())
    {
      _handcard.draw_card(n);
      return true;
    }
  return false;
}

void Player::init()					//game start init
{
  if (is_first)
    {
      for (int i = 0; i < 3; i++)
	draw();
      _mana.inc_max_mana(1);
      _mana.inc_cur_mana(1);
    }
  else
    {
      for (int i = 0; i < 4; i++)
	draw();
    }
}

void Player::turn()
{
  //preparation
  if ( _mana._max_mana < 10 ) //max mana++ & restore mana
    _mana.inc_max_mana();
  _mana.restore_mana();
  draw();
}

// use ith handcard
bool Player::use(int i)
{
  if (_handcard.getCost(i) > _mana.cur_mana())
    return false;
  Card *card = _handcard.use_card(i);
  _mana.cost_mana(card->cost());
  switch (card->_type)
    {
    case MINION:
      MinionCard *c = (MinionCard *)card;
      _battlefield->summon_minion(c->minion());
      break;
    default:
      break;
    }
  return true;
}

bool attack(int self, int other)
{
  Character *a, *b;
  if (self < 0)
    a = _battlefield->_hero[0];
  else
    a = _battlefield->_minion[0][self];
  if (other < 0)
    b = _battlefield->_hero[1];
  else
    b = _battlefield->_minion[1][other];
  if (!_battlefield->attack(a, b))
    return false;
  _battlefield->checkAndDead();
  return true;
}
