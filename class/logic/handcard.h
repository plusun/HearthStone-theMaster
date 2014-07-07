#ifndef __HADNSCARD_H__
#define __HANDSCARD_H__

#include "card.h"

#define MAXHCARD 10

class Handcard
{
public:
  vector<int> _card;
  Handcard():amount(0)
  {
    _card.clear();
  }
  void draw_card(int c)
  {
    _card.push_back(c);
  }
  Card *use_card(int position)
  {
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
