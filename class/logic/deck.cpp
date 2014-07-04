#include "deck.h"

deck::deck()
	:_amount(deck_amount)
{
	srand(time(0));
	for (int i = deck_amount -1; i > 0; i--)		//shuffle card
	{
		int p = rand() % i;
		int t = _card[deck_amount];
		_card[deck_amount] = _card[p];
		_card[p] = t;
	}

}

int deck::give_card()
{
	return _card[--_amount];
}