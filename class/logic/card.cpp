#include "card.h"
#include "minion.h"

Card *NumberToCard(int no)
{
  return new MinionCard(1, new Wisp());
}

