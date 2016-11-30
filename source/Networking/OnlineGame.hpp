#ifndef ONLINE_GAME_HPP
#define ONLINE_GAME_HPP

#include "../GameLogic/Player.hpp"
#include "TCPConnection.hpp"
#include <string>
#include <vector>

enum State { PASSING, BIDDING, PLAYING, ROUND_OVER, GAME_OVER };

class OnlineGame {
protected:
  std::vector<Player> players;
  TCPConnection::pointer connection;
  State s;
  virtual void receivedServerRequest(std::string){};
  virtual void sendServerResponse(std::string){};

public:
  OnlineGame(TCPConnection::pointer);
};

#endif
