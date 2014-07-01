#include "basic.h"
#include "character.h"

class Card
{
private:
  Value _cost;
public:
  Card(Value c):
    _cost(c)
  {
  }
  Value cost()
  {
    return _cost;
  }
  void cost(Value new_cost)
  {
    _cost = new_cost;
  }
};

class MinionCard: public Card
{
private:
  Minion *_minion;
public:
  MinionCard(Value cost, Minion *m):
    Card(cost), _minion(m)
  {
  }
  ~MinionCard()
  {
    if (_minion != NULL)
      delete _minion;
  }
  Minion *minion()
  {
    return _minion;
  }
  void minion(Minion *new_minion)
  {
    _minion = new_minion;
  }
};
