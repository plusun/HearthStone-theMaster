#ifndef _MINION_CLASS_
#define _MINION_CLASS_

#include "character.h"
#include "spell.h"

#define MAXMINION 35

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
    Minion(beast, 4, 2)
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

class ChillwindYeti: public Minion // Ñ©°Ö°Ö cost 4
{
public:
  ChillwindYeti():
    Minion(none, 5, 4)
  {
    no = MAXHERONO + 6;
  }
};

class CoreHound: public Minion // µØÓüÈÛÑÒÈ® cost 7
{
public:
  CoreHound():
    Minion(beast, 5, 9)
  {
    no = MAXHERONO + 7;
  }
};

class WarGolem: public Minion // Õ½¶·¿þÀÜ  cost 7
{
public:
  WarGolem():
    Minion(none, 7, 7)
  {
    no = MAXHERONO + 8;
  }
};

class BoulderfistOgre: public Minion //  ÀÏ±Ï cost 6
{
public:
  BoulderfistOgre():
    Minion(none, 7, 6)
  {
    no = MAXHERONO + 9;
  }
};

class MagmaRager: public Minion // ÎåÒ»ÖÁ×ð cost 3
{
public:
  MagmaRager():
    Minion(none, 1, 5)
  {
    no = MAXHERONO + 10;
  }
};

class MurlocRaider: public Minion //ÓãÈË 1-2-1 cost 1
{
public:
  MurlocRaider():
    Minion(murloc, 1, 2)
  {
    no = MAXHERONO + 11;
  }
};

class OasisSnapjaw: public Minion //  ´óÎÚ¹ê	cost 4
{
public:
  OasisSnapjaw():
    Minion(beast, 7, 2)
  {
    no = MAXHERONO + 12;
  }
};

class RiverCrocolisk: public Minion // µ­Ë®öù cost 2
{
public:
  RiverCrocolisk():
    Minion(beast, 3, 2)
  {
    no = MAXHERONO + 13;
  }
};

class FenCreeper: public Minion // 沼泽爬行者 cost 5
{
public:
  FenCreeper():
    Minion(none, 6, 3)
  {
    no = MAXHERONO + 14;
    buff._taunt = true;
  }
};

class Gnoll: public Minion // 霜狼步兵 cost 2
{
public:
  Gnoll():
    Minion(none, 2, 2)
  {
    no = MAXHERONO + 15;
    buff._taunt = true;
  }
};

class MoguShanWarden: public Minion // 远山守护者 cost 4
{
public:
  MoguShanWarden():
    Minion(none, 7, 1)
  {
    no = MAXHERONO + 16;
    buff._taunt = true;
  }
};

class Shieldbearer: public Minion // 护盾卫士 cost 1
{
public:
  Shieldbearer():
    Minion(none, 4, 0)
  {
    no = MAXHERONO + 17;
    buff._taunt = true;
  }
};

class BootyBayBodyguard: public Minion // 站在我身后就好了 cost 5
{
public:
  BootyBayBodyguard():
    Minion(none, 4, 5)
  {
    no = MAXHERONO + 18;
    buff._taunt = true;
  }
};

class GoldshireFootman: public Minion // 啥卫士 cost 1
{
public:
  GoldshireFootman():
    Minion(none, 2, 1)
  {
    no = MAXHERONO + 19;
    buff._taunt = true;
  }
};

class IronbarkProtector: public Minion // 88大树 cost 8
{
public:
  IronbarkProtector():
    Minion(none, 8, 8)
  {
    no = MAXHERONO + 20;
    buff._taunt = true;
  }
};

class LordOfTheArena: public Minion // 竞技场主宰 cost 6
{
public:
  LordOfTheArena():
    Minion(none, 5, 6)
  {
    no = MAXHERONO + 21;
    buff._taunt = true;
  }
};

class SenJinShieldmasta: public Minion // 帕金森卫士 cost 4
{
public:
  SenJinShieldmasta():
    Minion(none, 5, 3)
  {
    no = MAXHERONO + 22;
    buff._taunt = true;
  }
};

class Voidwalker: public Minion // 你为什么要召唤我? cost 1
{
public:
  Voidwalker():
    Minion(demon, 3, 1)
  {
    no = MAXHERONO + 23;
    buff._taunt = true;
  }
};

class KingKrush: public Minion // 橙卡,霸王龙 冲锋 cost 9
{
public:
  KingKrush():
    Minion(beast, 8, 8)
  {
    no = MAXHERONO + 24;
    buff._charge = true;
  }
};

class DruidOfTheClaw: public Minion // 德鲁伊之爪? 冲锋 cost 5
{
public:
  DruidOfTheClaw():
    Minion(none, 4, 4)
  {
    no = MAXHERONO + 25;
    buff._charge = true;
  }
};

class BluegillWarrior: public Minion // 蓝鳃战士  cost 2
{
public:
  BluegillWarrior():
    Minion(murloc, 1, 2)
  {
    no = MAXHERONO + 26;
    buff._charge = true;
  }
};

class Huffer: public Minion // 冲锋猪 cost 3
{
public:
  Huffer():
    Minion(beast, 2, 4)
  {
    no = MAXHERONO + 27;
    buff._charge = true;
  }
};

class KorKronElite: public Minion // 啥战士,我也不知道 冲锋 cost 4
{
public:
  KorKronElite():
    Minion(none, 3, 4)
  {
    no = MAXHERONO + 28;
    buff._charge = true;
  }
};

class StormwindKnight: public Minion // 暴风雪勇士? cost 4
{
public:
  StormwindKnight():
    Minion(none, 5, 2)
  {
    no = MAXHERONO + 29;
    buff._charge = true;
  }
};

class RecklessRocketeer: public Minion // 鲁莽火箭兵 cost 6
{
public:
  RecklessRocketeer():
    Minion(none, 2, 5)
  {
    no = MAXHERONO + 30;
    buff._charge = true;
  }
};

class StonetuskBoar: public Minion // 冲锋野猪 cost 1
{
public:
  StonetuskBoar():
    Minion(beast, 1, 1)
  {
    no = MAXHERONO + 31;
    buff._charge = true;
  }
};

class Wolfrider: public Minion // 狼骑兵出动 cost 3
{
public:
  Wolfrider():
    Minion(none, 1, 3)
  {
    no = MAXHERONO + 32;
    buff._charge = true;
  }
};

class ThrallmarFarseer: public Minion // 萨尔玛先知 cost 3
{
public:
  ThrallmarFarseer():
    Minion(none, 3, 2)
  {
    no = MAXHERONO + 33;
    buff._windfury = true;
  }
};

class WindfuryHarpy: public Minion // 风怒的鹰身女妖 cost 6
{
public:
  WindfuryHarpy():
    Minion(none, 5, 4)
  {
    no = MAXHERONO + 34;
    buff._windfury = true;
  }
};

class YoungDragonhawk: public Minion // 幼龙鹰 cost 1
{
public:
  YoungDragonhawk():
    Minion(beast, 1, 1)
  {
    no = MAXHERONO + 35;
    buff._windfury = true;
  }
};

#endif

