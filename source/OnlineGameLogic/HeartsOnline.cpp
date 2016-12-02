#include "HeartsOnline.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio/io_service.hpp>
#include <sstream>

HeartsOnline::HeartsOnline(wxFrame *mainFrame)
    : OnlineGame(mainFrame), ourTurn(false) {
  gui = new heartsArea(mainFrame);
  gui->setMadeMoveFunction([this](Card c) { humanMadeMove(c); });
}

void HeartsOnline::giveMove() { std::cout << "It's our move!" << std::endl; }

void HeartsOnline::humanMadeMove(Card c) {
  if (ourTurn) {
    std::stringstream serialize;
    boost::archive::text_oarchive oArchive(serialize);
    oArchive << c;
    mainFrame->sendServerMsg(serialize.str());
  }
}

void HeartsOnline::givePass() {}

void HeartsOnline::invalidMove() { gui->invalidMoveDialog(); }

void HeartsOnline::updateGameStatus(std::string msg) {
  GameMessage decodedGameMessage = decodeGameMessage(msg);
  state = decodedGameMessage.s;
  ourTurn = decodedGameMessage.turn;

  std::vector<int> handSizes = decodedGameMessage.handSizes;
  std::vector<Card> hand = decodedGameMessage.playerHand;
  std::vector<Card> field = decodedGameMessage.field;
  // I think we need a turn to know how to render the hand sizes

  // gui->updateOnlinePlayArea(hand, handSizes, field);
}

GameMessage HeartsOnline::decodeGameMessage(std::string msg) {
  std::stringstream message(msg);
  boost::archive::text_iarchive coded(message);
  GameMessage decodedGameMessage;
  coded >> decodedGameMessage;
  return decodedGameMessage;
}
