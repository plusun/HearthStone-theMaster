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
  int side;
public:
  Player(deck *d, Battlefield *b, bool f, int side);
  void init();
  void turn();
  void over();
  bool use(int);
  // return false if too many handcards
  bool draw();
  // self means my character, -1 stands for HERO, 0..+inf stands for minions
  // whichSide means which side I'll attack
  // whichCharacter means I wanna attack which charcter
  bool attack(int self, int whichSide, int whichCharacter);
};


#endif
