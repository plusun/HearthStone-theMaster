#ifndef __HADNSCARD_H__
#define __HANDSCARD_H__

#include "card.h"

#define MAXHCARD 100

class Handcard
{
public:
  vector<int> _card;
  Handcard()
  {
    _card.clear();
  }
  void draw_card(int c)
  {
    _card.push_back(c);
  }
  int getCost(int position)
  {
    Card *card = NumberToCard(_card[position]);
    int ret = card->cost();
    return ret;
  }
  Card *use_card(int position)
  {
    if (position >= _card.size())
      return NULL;
    int tmp = _card[position];
    _card.erase(_card.begin() + position);
    return NumberToCard(tmp);
  }
  bool full()
  {
    return _card.size() >= MAXHCARD;
  }
};

#endif
