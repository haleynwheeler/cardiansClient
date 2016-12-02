#ifndef HEARTS_ONLINE_HPP
#define HEARTS_ONLINE_HPP

//#include "../GameLogic/Card.hpp"
//#include "../GameLogic/Player.hpp"
#include "../Messages/GameMessage.hpp"
#include "../heartsArea.h"
#include "OnlineGame.hpp"

class HeartsOnline : public OnlineGame {
private:
  bool ourTurn;
  heartsArea *gui;
  void giveMove();
  void givePass();
  void invalidMove();
  void updateGameStatus(std::string);
  void humanMadeMove(Card);
  GameMessage decodeGameMessage(std::string);

public:
  HeartsOnline(wxFrame *);
};

#endif
