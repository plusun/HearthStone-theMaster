#include "card.h"

class Handcard
{
public:
	int amount;
	vector<Card> _card;
	Handcard():amount(0)
	{
		_card.clear();
	}
	void draw_card(Card c)
	{
		amount++;
		_card.push_back(c);
	}
	Card use_card(int position)
	{
		for (int i = position; i < amount - 1; i++)
			_card[i] = _card[i+1];
		amount--;
		Card tmp_card = _card.back();
		_card.pop_back();
		return tmp_card;
	}

};