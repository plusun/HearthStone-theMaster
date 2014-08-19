#ifndef __DECK_H__
#define __DECK_H__

#include "card.h"
#include <ctime>
#include <fstream>
#define deck_amount 30

class deck
{
public:
  deck();
  int _amount;
  int _card[deck_amount];
  int give_card();
};



#endif
