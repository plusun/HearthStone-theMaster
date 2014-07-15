#include "deck.h"

deck::deck()
  :_amount(deck_amount)
{
  srand(time(0));
  for (int i = 0; i < _amount; ++i)
    {
      _card[i] = rand() % MAXCARDNO + 1;
    }

}

int deck::give_card()
{
  return _card[--_amount];
}
