#include "basic.h"
#include "character.h"

class Battlefield
{
public:
	int amount;
	vector<Minion*> _minion;
	Battlefield():amount(0)
	{
		_minion.clear();
	}
	void summon_minion(minion* m, int position = -1,)
	{
		amount++;
		if (position == -1)
			_minion.push_back(m);
		else
		{
			_minion.push_back(m);
			for (int i = amount - 1; i != position; i--)
				_minion[i] = _minion[i-1];
			_minion[position] = m;
		}
	}
	void destroy_minion(int position)
	{
		delete _minion[position];
		for (int i = position; i < amount - 1; i++)
			_minion[i] = _minion[i+1];
		_minion.pop_back();
		amount--;
	}
}