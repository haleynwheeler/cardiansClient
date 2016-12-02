#ifndef CRAZY_EIGHTS_ONLINE_HPP
#define CRAZY_EIGHTS_ONLINE_HPP

//#include "../GameLogic/Card.hpp"
//#include "../GameLogic/Player.hpp"
#include "../Messages/GameMessage.hpp"
#include "../playArea.h"
#include "OnlineGame.hpp"

class CrazyEightsOnline : public OnlineGame {
private:
  bool ourTurn;
  playArea *gui;
  void giveMove();
  void giveSuit();
  void invalidMove();
  void updateGameStatus(std::string);
  void humanMadeMove(Card);
  void humanDrewCard();
  GameMessage decodeGameMessage(std::string);

public:
  CrazyEightsOnline(wxFrame *);
};

#endif
