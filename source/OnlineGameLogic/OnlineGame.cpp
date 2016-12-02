#include "OnlineGame.hpp"
#include "../Simple.h"

#include <boost/algorithm/string.hpp>

OnlineGame::OnlineGame(wxFrame *simple) : mainFrame((Simple *)simple) {
  // mainFrame = (Simple *)s = HASNT_STARTED;
  startListening();
}

void OnlineGame::startListening() {
  // Simple *mainFrame = (Simple *)GetParent();
  while (state != GAME_OVER) {
    auto serverMsg = mainFrame->getResponse();
    processRecievedMsgFromServer(serverMsg);
  }
}

void OnlineGame::processRecievedMsgFromServer(std::string msg) {
  if (boost::algorithm::starts_with(msg, "Give Move")) {
    giveMove();
  } else if (boost::algorithm::starts_with(msg, "Give Suit")) {
    giveSuit();
  } else if (boost::algorithm::starts_with(msg, "Status Update")) {
    auto newMsg = mainFrame->getResponse();
    updateGameStatus(newMsg);
  } else if (boost::algorithm::starts_with(msg, "Give Pass")) {
    givePass();
  } else if (boost::algorithm::starts_with(msg, "Invalid Move")) {
    invalidMove();
  } else {
    std::cout << "We don't know what this message means" << std::endl;
    std::cout << msg << std::endl;
  }
}
