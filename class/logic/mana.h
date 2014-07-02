#include "basic"

class Mana
{
private:
	Value _max_mana;
	Value _cur_mana;
public:
	Mana(Value mm = 0, Value cm = 0):_max_mana(mm),_cur_mana(cm){}
	Value max_mana()
	{
		return _max_mana;
	}
	Value cur_mana()
	{
		return _cur_mana;
	}
	void inc_max_mana(Value n = 1)
	{
		_max_mana += n;
	}
	void inc_cur_mana(Value n)
	{
		_cur_mana += n;
	}
	void cost_mana(Value n)
	{
		inc_cur_mana(0-n);
	}
};