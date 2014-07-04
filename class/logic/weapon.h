#include "basic.h"

class Weapon
{
private:
  Value _attack, _durable;
public:
  Weapon(Value a, Value d):
    _attack(a), _durable(d)
  {
  }
  Value attack()
  {
    return _attack;
  }
  void attack(Value new_attack)
  {
    _attack = new_attack;
  }
  Value durable()
  {
    return _durable;
  }
  void durable(Value new_durable)
  {
    _durable = new_durable;
  }
}