#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "basic.h"
#include "character.h"
#include "mana.h"
#include "battlefield.h"
#include "handcard.h"
#include "deck.h"

#define maxhp 30


class Sustainable_effect
{
public:
  checkpoint _time;
  Character _targe;
  void effect();
};

class Player
{
public:
  deck *_deck;
  Battlefield *_battlefield;
  Handcard _handcard;
  Mana _mana;
  //Secret_slot _secret;
  bool is_first;
public:
  Player(deck *d, Battlefield *b, bool f = true);
  void init();
  void turn();
  bool use(int);
  // return false if too many handcards
  bool draw();
  bool attack(int self, int other);
};


#endif
