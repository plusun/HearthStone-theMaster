#include "basic.h"

class Mana
{
private:
	int _max_mana;
	int _cur_mana;
public:
	Mana(int mm = 0, int cm = 0):_max_mana(mm),_cur_mana(cm){}
	int max_mana()
	{
		return _max_mana;
	}
	int cur_mana()
	{
		return _cur_mana;
	}
	void inc_max_mana(int n)
	{
		_max_mana += n;
	}
	void inc_cur_mana(int n)
	{
		_cur_mana += n;
	}
	void cost_mana(int n)
	{
		inc_cur_mana(0-n);
	}
	void restore_mana()
	{
		_cur_mana = _max_mana;
	}
};