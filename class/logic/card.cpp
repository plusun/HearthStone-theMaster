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
  if (cardPool.find(no) == cardPool.end())
    {
      MinionCard *card;
      switch (no)
	{
	case 1:
	  card = new MinionCard(1, NULL);
	  card->minion(new Wisp());
	  break;
	case 2:
	  card = new MinionCard(2, NULL);
	  card->minion(new BloodfenRaptor());
	case 3:
	  card = new MinionCard(2, NULL);
	  card->minion(new Amani());
	  break;
	case 4:
	  card = new MinionCard(3, NULL);
	  card->minion(new JunglePanther());
	  break;
	case 5:
	  card = new MinionCard(3, NULL);
	  card->minion(new IronfurGrizzly());
	  break;
      
	default:
	  return NULL;
	  break;
	}
      cardPool[no] = card;
    }
  return cardPool[no];
}

