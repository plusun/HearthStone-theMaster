#ifndef __DECK_H__
#define __DECK_H__

#include "card.h"
#include <ctime>
#define deck_amount 30

class deck
{
	int _amount;
	int _card[deck_amount];
public:
	deck();
	int give_card();
};



#endif