#ifndef __BASIC_H__
#define __BASIC_H__

#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum Race {none=0, beast, murloc, pirate, dragon, demon, totem};

enum checkpoint {turn_start = 0, summon_minion, want_to_attack, hurt, died, cast_spell, turn_end};


string convertInt(int number);


#endif
