#include "card.h"

class Handcard
{
public:
	int amount;
	vector<Card> _card;
	Handcard():amount(0)
	{
		_minion.clear();
	}
	void draw_card(Card c)
	{
		amount++;
		_card.push_back(c);
	}
	Card use card(int position)
	{
		for (int i = position; i < amount - 1; i++)
			_card[i] = _card[i+1];
		amount--;
		return _card.pop_back();
	}

}