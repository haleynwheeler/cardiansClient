#include "CrazyEightsOnline.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio/io_service.hpp>
#include <sstream>

CrazyEightsOnline::CrazyEightsOnline(wxFrame *mainFrame)
    : OnlineGame(mainFrame), ourTurn(false) {
  gui = new playArea(mainFrame);
  gui->setMadeMoveFunction([this](Card c) { humanMadeMove(c); });
  gui->setDrewCardFunction([this]() { humanDrewCard(); });
}

void CrazyEightsOnline::giveMove() {
  std::cout << "It's our move!" << std::endl;
}

void CrazyEightsOnline::humanMadeMove(Card c) {
  if (ourTurn) {
    std::stringstream serialize;
    boost::archive::text_oarchive oArchive(serialize);
    oArchive << c;
    mainFrame->sendServerMsg(serialize.str());
  }
}

void CrazyEightsOnline::humanDrewCard() {
  if (ourTurn) {
    Card cardToSerialize(UNDEFINED, TWO);
    std::stringstream serialize;
    boost::archive::text_oarchive oArchive(serialize);
    oArchive << cardToSerialize;
    mainFrame->sendServerMsg(serialize.str());
  }
}

void CrazyEightsOnline::giveSuit() {
  Suit decision = gui->userPickSuitDialog();
  while (decision == UNDEFINED) {
    decision = gui->userPickSuitDialog();
  }
  Card cardToSerialize(decision, EIGHT);
  std::stringstream serialize;
  boost::archive::text_oarchive oArchive(serialize);
  oArchive << cardToSerialize;
  mainFrame->sendServerMsg(serialize.str());
}

void CrazyEightsOnline::invalidMove() { gui->invalidMoveDialog(); }

void CrazyEightsOnline::updateGameStatus(std::string msg) {
  GameMessage decodedGameMessage = decodeGameMessage(msg);
  state = decodedGameMessage.s;
  ourTurn = decodedGameMessage.turn;

  std::vector<int> handSizes = decodedGameMessage.handSizes;
  std::vector<Card> hand = decodedGameMessage.playerHand;
  bool deckEmpty = decodedGameMessage.deckEmpty;
  // I think we need a turn to know how to render the hand sizes

  // gui->updateOnlinePlayArea(hand, handSizes, deckEmpty);
}

GameMessage CrazyEightsOnline::decodeGameMessage(std::string msg) {
  std::stringstream message(msg);
  boost::archive::text_iarchive coded(message);
  GameMessage decodedGameMessage;
  coded >> decodedGameMessage;
  return decodedGameMessage;
}
