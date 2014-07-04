#include "basic.h"

class Weapon
{
private:
  int _attack, _durable;
public:
  Weapon(int a, int d):
    _attack(a), _durable(d)
  {
  }
  int attack()
  {
    return _attack;
  }
  void attack(int new_attack)
  {
    _attack = new_attack;
  }
  int durable()
  {
    return _durable;
  }
  void durable(int new_durable)
  {
    _durable = new_durable;
  }
}