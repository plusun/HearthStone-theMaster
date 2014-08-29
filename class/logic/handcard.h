#ifndef __HADNSCARD_H__
#define __HANDSCARD_H__

#include "card.h"

#define MAXHCARD 100

class Handcard
{
public:
  vector<int> _card;
  Battlefield *bf;
  int side;
  Handcard(Battlefield *b, int s): bf(b), side(s)
  {
    _card.clear();
  }
  void draw_card(int c)
  {
    _card.push_back(c);
  }
  int getCost(int position)
  {
    Card *card = NumberToCard(_card[position], bf, side);
    int ret = card->cost();
    return ret;
  }
  Card *getCard(int position)
  {
    return NumberToCard(_card[position], bf, side);
  }
  Card *use_card(int position)
  {
    if (position >= _card.size())
      return NULL;
    int tmp = _card[position];
    _card.erase(_card.begin() + position);
    return NumberToCard(tmp, bf, side);
  }
  bool full()
  {
    return _card.size() >= MAXHCARD;
  }
};

#endif
