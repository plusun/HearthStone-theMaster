#include "card.h"
#define deck_amount 30

class deck
{
	int _amount;
	int _card[deck_amount];
public:
	deck();
	int give_card();
};


deck::deck()
	:amount(deck_amount)
{
	srand(time(0));
	for (int i = deck_amount -1; i > 0; i--)			//Ï´ÅÆ
	{
		int p = rand() % i;
		int t = _card[deck_amount];
		_card[deck_amount] = _card[p];
		_card[p] = t;
	}

}

int deck::give_card()
{

}