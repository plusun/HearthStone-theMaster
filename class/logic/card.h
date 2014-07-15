#ifndef __CARD_H__
#define __CARD_H__

#include "basic.h"
#include "character.h"
#include "cocos2d.h"
#include <map>

USING_NS_CC;

// max number of cards
#define MAXCARDNO 5

enum CardType { MINION, SPELL };

class Card
{
private:
  int _cost;
public:
  CardType _type;
  Card(int c, CardType t = MINION):
    _cost(c), _type(t)
  {
  }
  int cost()
  {
    return _cost;
  }
  void cost(int new_cost)
  {
    _cost = new_cost;
  }

  Sprite * Sprite_card;
};

class MinionCard: public Card
{
public:
  Minion *_minion;
  MinionCard(int cost, Minion *m):
    Card(cost), _minion(m)
  {
  }
  ~MinionCard()
  {
    if (_minion != NULL)
      delete _minion;
  }
  Minion *minion()
  {
    return _minion;
  }
  void minion(Minion *new_minion)
  {
    _minion = new_minion;
  }
};
extern std::map<int, Card *> cardPool;
Card *NumberToCard(int no);

#endif
