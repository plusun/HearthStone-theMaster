#ifndef _MINION_CLASS_
#define _MINION_CLASS_

#include "character.h"
#include "spell.h"

#define MAXMINION 20

class Wisp: public Minion
{
public:
  Wisp():
    Minion(none, 1, 100)
  {
    no = MAXHERONO + 1;
  }
};

class BloodfenRaptor: public Minion
{
public:
  BloodfenRaptor():
    Minion(beast, 2, 3)
  {
    no = MAXHERONO + 2;
  }
};

class Amani: public Minion
{
public:
  Amani():
    Minion(none, 3, 2)
  {
    no = MAXHERONO + 3;
  }
};

class JunglePanther: public Minion
{
public:
  JunglePanther():
    Minion(beast, 2, 4)
  {
    no = MAXHERONO + 4;
  }
};

class IronfurGrizzly: public Minion
{
public:
  IronfurGrizzly():
    Minion(beast, 3, 3)
  {
    no = MAXHERONO + 5;
	buff._taunt = true;
  }
};

class ChillwindYeti: public Minion // ѩ�ְ� cost 4
{
public:
  ChillwindYeti():
    Minion(none, 4, 5)
  {
    no = MAXHERONO + 6;
  }
};

class CoreHound: public Minion // ��������Ȯ cost 7
{
public:
  CoreHound():
    Minion(beast, 9, 5)
  {
    no = MAXHERONO + 7;
  }
};

class WarGolem: public Minion // ս������  cost 7
{
public:
  WarGolem():
    Minion(none, 7, 7)
  {
    no = MAXHERONO + 8;
  }
};

class BoulderfistOgre: public Minion //  �ϱ� cost 6
{
public:
  BoulderfistOgre():
    Minion(none, 6, 7)
  {
    no = MAXHERONO + 9;
  }
};

class MagmaRager: public Minion // ��һ���� cost 3
{
public:
  MagmaRager():
    Minion(none, 5, 1)
  {
    no = MAXHERONO + 10;
  }
};

class MurlocRaider: public Minion //���� 1-2-1 cost 1
{
public:
  MurlocRaider():
    Minion(murloc, 2, 1)
  {
    no = MAXHERONO + 11;
  }
};

class OasisSnapjaw: public Minion //  ���ڹ�	cost 4
{
public:
  OasisSnapjaw():
    Minion(beast, 2, 7)
  {
    no = MAXHERONO + 12;
  }
};

class RiverCrocolisk: public Minion // ��ˮ�� cost 2
{
public:
  RiverCrocolisk():
    Minion(beast, 2, 3)
  {
    no = MAXHERONO + 13;
  }
};
#endif

