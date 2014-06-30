#include "basic.h"

class Card
{
private:
  Value _cost;
public:
  Value cost()
  {
    return _cost;
  }
  void cost(Value new_cost)
  {
    _cost = new_cost;
  }
}
