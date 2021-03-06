#include "basic.h"
#include "card.h"
#include "minion.h"
#include "spell.h"

string NumberToFilename(int no)
{
  return convertInt(no) + ".png";
}

Card *NumberToCard(int no, Battlefield *bf, int side)
{
  Card *card = NULL;
  MinionCard *mcard = NULL;
  SpellCard* scard = NULL;
  Spell *spell;
  switch (no)
    {
    case 1:
      mcard = new MinionCard(0, NULL);
      mcard->minion(new Wisp());
      break;
    case 2:
      mcard = new MinionCard(2, NULL);
      mcard->minion(new BloodfenRaptor());
      break;
    case 3:
      mcard = new MinionCard(2, NULL);
      mcard->minion(new Amani());
      break;
    case 4:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new JunglePanther());
      break;
    case 5:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new IronfurGrizzly());
      break;
    case 6:
      if (bf == NULL)
	return NULL;
      spell = new Flamestrike(bf, side);
      scard = new SpellCard(7, spell);
      break;
    case 7:
      if (bf == NULL)
	return NULL;
      spell = new Consecration(bf, side);
      scard = new SpellCard(4, spell);
      break;
    case 8:
      if (bf == NULL)
	return NULL;
      spell = new ArcaneExplosion(bf, side);
      scard = new SpellCard(2, spell);
      break;
    case 9:
      if (bf == NULL)
	return NULL;
      spell = new Fireball(bf, side);
      scard = new SpellCard(4, spell);
      break;      
    case 10:
      if (bf == NULL)
	return NULL;
      spell = new Moonfire(bf, side);
      scard = new SpellCard(0, spell);
      break;      
    case 11:
      if (bf == NULL)
	return NULL;
      spell = new Starfall(bf, side);
      scard = new SpellCard(5, spell);
      break;      
    case 12:
      if (bf == NULL)
	return NULL;
      spell = new Pyroblast(bf, side);
      scard = new SpellCard(10, spell);
      break;      
    case 13:
      if (bf == NULL)
	return NULL;
      spell = new HolyLight(bf, side);
      scard = new SpellCard(2, spell);
      break;      
    case 14:
      if (bf == NULL)
	return NULL;
      spell = new Assassinate(bf, side);
      scard = new SpellCard(5, spell);
      break;      
    case 15:
      if (bf == NULL)
	return NULL;
      spell = new TwistingNether(bf, side);
      scard = new SpellCard(8, spell);
      break;      
    case 16:
      if (bf == NULL)
	return NULL;
      spell = new Hellfire(bf, side);
      scard = new SpellCard(4, spell);
      break;      
    case 17:
      if (bf == NULL)
	return NULL;
      spell = new ShadowBolt(bf, side);
      scard = new SpellCard(3, spell);
      break;      
    case 18:
      if (bf == NULL)
	return NULL;
      spell = new ArcaneShot(bf, side);
      scard = new SpellCard(1, spell);
      break;      
    case 19:
      if (bf == NULL)
	return NULL;
      spell = new CircleOfHealing(bf, side);
      scard = new SpellCard(0, spell);
      break;
    case 20:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new ChillwindYeti());
      break;
    case 21:
      mcard = new MinionCard(7, NULL);
      mcard->minion(new CoreHound());
      break;
    case 22:
      mcard = new MinionCard(7, NULL);
      mcard->minion(new WarGolem());
      break;
    case 23:
      mcard = new MinionCard(6, NULL);
      mcard->minion(new BoulderfistOgre());
      break;
    case 24:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new MagmaRager());
      break;
    case 25:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new MurlocRaider());
      break;
    case 26:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new OasisSnapjaw());
      break;
    case 27:
      mcard = new MinionCard(2, NULL);
      mcard->minion(new RiverCrocolisk());
      break;
    case 28:
      mcard = new MinionCard(5, NULL);
      mcard->minion(new FenCreeper());
      break;
    case 29:
      mcard = new MinionCard(2, NULL);
      mcard->minion(new Gnoll());
      break;
    case 30:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new MoguShanWarden());
      break;
    case 31:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new Shieldbearer());
      break;
    case 32:
      mcard = new MinionCard(5, NULL);
      mcard->minion(new BootyBayBodyguard());
      break;
    case 33:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new GoldshireFootman());
      break;
    case 34:
      mcard = new MinionCard(8, NULL);
      mcard->minion(new IronbarkProtector());
      break;
    case 35:
      mcard = new MinionCard(6, NULL);
      mcard->minion(new LordOfTheArena());
      break;
    case 36:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new SenJinShieldmasta());
      break;
    case 37:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new Voidwalker());
      break;
    case 38:
      mcard = new MinionCard(9, NULL);
      mcard->minion(new KingKrush());
      break;
    case 39:
      mcard = new MinionCard(5, NULL);
      mcard->minion(new DruidOfTheClaw());
      break;
    case 40:
      mcard = new MinionCard(2, NULL);
      mcard->minion(new BluegillWarrior());
      break;
    case 41:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new Huffer());
      break;
    case 42:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new KorKronElite());
      break;
    case 43:
      mcard = new MinionCard(4, NULL);
      mcard->minion(new StormwindKnight());
      break;
    case 44:
      mcard = new MinionCard(6, NULL);
      mcard->minion(new RecklessRocketeer());
      break;
    case 45:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new StonetuskBoar());
      break;
    case 46:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new Wolfrider());
      break;
    case 47:
      mcard = new MinionCard(3, NULL);
      mcard->minion(new ThrallmarFarseer());
      break;
    case 48:
      mcard = new MinionCard(6, NULL);
      mcard->minion(new WindfuryHarpy());
      break;
    case 49:
      mcard = new MinionCard(1, NULL);
      mcard->minion(new YoungDragonhawk());
      break;
    default:
      return NULL;
      break;
    }
  if (scard != NULL)
    card = scard;
  if (mcard != NULL)
    card = mcard;
  return card;
}

