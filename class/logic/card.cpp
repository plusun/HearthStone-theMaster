#include "card.h"
#include "minion.h"

std::map<int, Card *> cardPool;

Card *NumberToCard(int no)
{
	if (cardPool.find(no) == cardPool.end())
		cardPool[no] = new MinionCard(1, new Wisp());
  return cardPool[no];
}

