#ifndef _CLASS_GAME_
#define _CLASS_GAME_

#include "player.h"

class Game
{
  Player* _p1;
  Player* _p2;
  Game();
  void play();
};

Game::Game()
{
  _p1 = new Player;
  _p2 = new Player;
  _p1->init();
  _p2->init();
  bool t = false; //receive_from_server();
  if (t)
    _p1->is_first = true;
  else
    _p2->is_first = true;
  _p1->is_host = true;
}

void Game::play()
{
  while (1)
    {
      //      _p1.turn();
      //      _p2.turn();
    }

}
#endif
