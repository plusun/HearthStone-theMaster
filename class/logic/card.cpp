#include "card.h"
#include "minion.h"
#include <string>
#include <stringstream>

std::map<int, Card *> cardPool;

string convertInt(int number)
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}

string NumberToFilename(int no)
{
  return convertInt(no) + ".jpg";
}

Card *NumberToCard(int no)
{
  switch (no)
    {
    case 1:
      if (cardPool.find(no) == cardPool.end())
	cardPool[no] = new MinionCard(1, NULL);
      cardPool[no]->minion(new Wisp());
      break;
    case 2:
      if (cardPool.find(no) == cardPool.end())
	cardPool[no] = new MinionCard(2, NULL);
      cardPool[no]->minion(new BloodfenRaptor());
    case 3:
      if (cardPool.find(no) == cardPool.end())
	cardPool[no] = new MinionCard(2, NULL);
      cardPool[no]->minion(new Amani());
      break;
    case 4:
      if (cardPool.find(no) == cardPool.end())
	cardPool[no] = new MinionCard(3, NULL);
      cardPool[no]->minion(new JunglePanther());
      break;
    case 5:
      if (cardPool.find(no) == cardPool.end())
	cardPool[no] = new MinionCard(3, NULL);
      cardPool[no]->minion(new IronfurGrizzly());
      break;
      
    default:
      return NULL;
      break;
    }
  return cardPool[no];
}

