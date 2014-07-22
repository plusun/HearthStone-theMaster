#include "player.h"


Player::Player(deck *d, Battlefield *b, bool f, int s):
  _deck(d), _battlefield(b), is_first(f), side(s)
{
}

bool Player::draw()
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
    }
  else
    {
      for (int i = 0; i < 4; i++)
	draw();
    }
}

void Player::turn()
{
  _battlefield->startSide(side);
  //preparation
  if ( _mana._max_mana < 10 ) //max mana++ & restore mana
    _mana.inc_max_mana();
  _mana.restore_mana();
  //draw();
}

void Player::over()
{
  _battlefield->overSide(side);
}

// use ith handcard
bool Player::use(int i, int pos)
{
  if (_handcard.getCost(i) > _mana.cur_mana())
    return false;
  Card *card = _handcard.use_card(i);
  if (card == NULL)
    return false;
  _mana.cost_mana(card->cost());
  MinionCard *c = NULL;
  switch (card->_type)
    {
    case MINION:
      c = (MinionCard *)card;
      _battlefield->summon_minion(c->minion() , this->side , pos);
      break;
    default:
      break;
    }
  _battlefield->checkAndDead();
  return true;
}

bool Player::attack(int self, int whichSide, int other)
{
  if (whichSide == side)
    return false;
  Character *a, *b;
  if (self < 0)
    a = _battlefield->_hero[side];
  else
    a = _battlefield->_minion[side][self];
  if (other < 0)
    b = _battlefield->_hero[whichSide];
  else
    b = _battlefield->_minion[whichSide][other];
  if (!_battlefield->attack(a, b))
    return false;
  _battlefield->checkAndDead();
  return true;
}
