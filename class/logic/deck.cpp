#include "deck.h"

deck::deck()
  :_amount(deck_amount)
{
  	srand((unsigned)time(NULL));
	ifstream file("deck.txt",ios::in);
	for (int i = 0; i < _amount; i++)
		file >> _card[i];
	for (int i = _amount-1; i > 1; i--)
	{
	  int tmp = rand() % (i + 1);
		int tmp2;
		tmp2 = _card[tmp];
		_card[tmp] = _card[i];
		_card[i] = tmp2;
	}
	file.close();
}

int deck::give_card()
{
  return _card[--_amount];
}
