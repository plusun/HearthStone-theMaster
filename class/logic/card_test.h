#include "card.h"
#include "spell.h"
#include "minion_test.h"

class Wisp_card : public Minion_card
{
public:
	Wisp_card(1,NULL);
}

Wisp_card::cast()
{
	_minion = new Wisp;

}