#include "card.h"
#include "minion.h"
#include <string>
#include <sstream>

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
	MinionCard *card;
  switch (no)
    {
    case 1:
      if (cardPool.find(no) == cardPool.end())
	card = new MinionCard(1, NULL);
      card->minion(new Wisp());
	  cardPool[no] = card;
      break;
    case 2:
      if (cardPool.find(no) == cardPool.end())
	card = new MinionCard(2, NULL);
      card->minion(new BloodfenRaptor());
	  cardPool[no] = card;
    case 3:
      if (cardPool.find(no) == cardPool.end())
	card = new MinionCard(2, NULL);
      card->minion(new Amani());
	  cardPool[no] = card;
      break;
    case 4:
      if (cardPool.find(no) == cardPool.end())
	card = new MinionCard(3, NULL);
      card->minion(new JunglePanther());
	  cardPool[no] = card;
      break;
    case 5:
      if (cardPool.find(no) == cardPool.end())
	card = new MinionCard(3, NULL);
      card->minion(new IronfurGrizzly());
	  cardPool[no] = card;
      break;
      
    default:
      return NULL;
      break;
    }
  return cardPool[no];
}

