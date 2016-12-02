#ifndef ONLINE_GAME_HPP
#define ONLINE_GAME_HPP

#include "../GameLogic/Player.hpp"
#include "../Simple.h"
#include <string>

// enum State { PASSING, BIDDING, PLAYING, ROUND_OVER, GAME_OVER, HASNT_STARTED
// };

class OnlineGame {
private:
  void startListening();
  void processRecievedMsgFromServer(std::string);

protected:
  Simple *mainFrame;
  State state;
  virtual void giveMove() = 0;
  virtual void giveSuit(){};
  virtual void givePass(){};
  virtual void updateGameStatus(std::string) = 0;
  virtual void invalidMove() = 0;

public:
  OnlineGame(wxFrame *simple);
};

#endif
