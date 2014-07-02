#include "card.h"

class Handcard
{
public:
	int amount;
	vector<card> _card;
	Handcard():amount(0)
	{
		_minion.clear();
	}
	void draw_card(card c)
	{
		amount++;
		_minion.push_back(m);
	}
	void use card(int position)
	{
		for (int i = position; i < amount - 1; i++)
			_card[i] = _card[i+1];
		_card.pop_back();
		amount--;
	}

};