#ifndef _MINION_CLASS_
#define _MINION_CLASS_

#include "character.h"
#include "spell.h"

class Wisp: public Minion
{
public:
  Wisp():
    Minion(none, 1, 1) {}
};

class BloodfenRaptor: public Minion
{
public:
  BloodfenRaptor():
    Minion(beast, 3, 2) {}
};

class Amani: public Minion
{
public:
  Amani():
    Minion(none, 2, 3) {}
};

class JunglePanther: public Minion
{
public:
  JunglePanther():
    Minion(beast, 4, 2) {}
};

class IronfurGrizzly: public Minion
{
  IronfurGrizzly():
    Minion(beast, 3, 3) {}
};
#endif
