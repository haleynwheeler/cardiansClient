#ifndef CRAZY_EIGHTS_ONLINE_HPP
#define CRAZY_EIGHTS_ONLINE_HPP

#include "../playArea.h"
#include "OnlineGame.hpp"

class CrazyEightsOnline : public OnlineGame {
private:
  playArea *gui;
  int turn;
  std::vector<int> sizeOfPlayersHands;
  std::vector<Card> yourHand;
  Card topOfDiscardPile;
  bool deckEmpty;
  void receivedServerRequest(std::string);
  void sendServerResponse(std::string);

public:
  CrazyEightsOnline(TCPConnection::pointer, wxFrame *);
};

#endif
