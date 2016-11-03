#include "Game.hpp"
#include <chrono>
#include <random>
#include <thread>
#include <wx/wx.h>

using namespace std::chrono_literals;

CrazyEightsGame::CrazyEightsGame(wxFrame *mainFrame) {
  std::cout << "Creating Crazy Eights Game" << std::endl;
  // Construct a Player Named "You". This will be our Human Player.
  players.push_back(Player(0, "You"));

  // Construct the AI Players.
  for (auto i = 1; i < 4; i++) {
    players.push_back(Player(0, "AI"));
  }
  gui = new playArea(mainFrame);
  startNewRound();
}

CrazyEightsGame::~CrazyEightsGame() {}

void CrazyEightsGame::startNewRound() {
  deck = initializeDeck();
  for (auto &&player : players) {
    player.startNewRound();
    player.initializeHand(deck, 5);
  }
  int i = 0;
  while (deck.back().getValue() == EIGHT) {
    std::swap(deck.back(), deck[i]);
    i++;
  }
  auto topOfDiscardPile = deck.back();
  discardPile.push_back(topOfDiscardPile);
  deck.pop_back();
  turn = 0;
  gui->updatePlayArea(0, players[0].getHand(), false, topOfDiscardPile);
}

// THIS SHOULD BE CALLED WHEN THE DECK IS PRESSED
void CrazyEightsGame::humanDrewCard() {
  if (turn == 0) {
    if (!deck.empty()) {
      players[0].insertCardToHand(deck.back());
      deck.pop_back();
      gui->updatePlayArea(0, players[0].getHand(), deck.empty(),
                          discardPile.back());
    } else {
      auto hand = players[0].getHand();
      for (auto &&card : hand) {
        auto validMove = checkCardValidity(card);
        if (!validMove) {
          gui->invalidMoveDialog();
          return;
        }
      }
      computersTurn();
    }
  }
}

// THIS SHOULD BE CALLED WHEN A CARD IN THE HAND IS PRESSED
void CrazyEightsGame::humanMadeMove(Card c) {
  if (turn == 0) {
    auto validMove = checkCardValidity(c) && removeCardFromHand(c);
    if (validMove) {
      if (players[0].getHand().size() == 0) {
        endRound();
      } else if (c.getValue() == EIGHT) {
        suitSpecified = gui->userPickSuitDialog();
      }
      gui->updatePlayArea(0, players[0].getHand(), deck.empty(),
                          discardPile.back());
      computersTurn();
    } else {
      gui->invalidMoveDialog();
    }
  }
}

void CrazyEightsGame::computersTurn() {
  for (int i = 1; i < 4; i++) {
    turn = i;
    computersMove();
    gui->updatePlayArea(i, players[i].getHand(), deck.empty(),
                        discardPile.back());
    std::this_thread::sleep_for(2s);
  }
  turn = 0;
}

void CrazyEightsGame::computersMove() {
  auto hand = players[turn].getHand();
  for (auto &&card : hand) {
    auto validMove = checkCardValidity(card);
    if (validMove) {
      performValidAiMove(card);
      return;
    }
  }
  while (deck.size() > 0) {
    auto newCard = deck.back();
    deck.pop_back();
    players[turn].insertCardToHand(newCard);
    auto validMove = checkCardValidity(newCard);
    if (validMove) {
      performValidAiMove(newCard);
      return;
    }
  }
}

void CrazyEightsGame::performValidAiMove(Card card) {
  players[turn].removeCardFromHand(card);
  if (players[turn].getHand().size() == 0) {
    endRound();
  } else if (card.getValue() == EIGHT) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 3);
    suitSpecified = static_cast<Suit>(dist(rd));
    gui->aiPickedSuitDialog(suitSpecified);
  }
}

bool CrazyEightsGame::checkCardValidity(Card c) {
  auto cardToMatch = discardPile.back();
  if (cardToMatch.getValue() == EIGHT) {
    if (c.getSuit() == suitSpecified) {
      return true;
    }
  } else if (c.getValue() == EIGHT || c.getSuit() == cardToMatch.getSuit() ||
             c.getValue() == cardToMatch.getValue()) {
    return true;
  }
  return false;
}

bool CrazyEightsGame::removeCardFromHand(Card c) {
  auto successfullyRemoved = players[turn].removeCardFromHand(c);
  if (successfullyRemoved) {
    discardPile.push_back(c);
    return true;
  } else {
    return false;
  }
}

void CrazyEightsGame::endRound() {
  // Calculate Scores:
  for (auto &&player : players) {
    for (auto &&card : player.getHand()) {
      auto value = card.getValue();
      if (value == EIGHT) {
        player.incrementRoundScore(50);
      } else if (value == TEN || value == JACK || value == QUEEN ||
                 value == KING) {
        player.incrementRoundScore(10);
      } else if (value == ACE) {
        player.incrementRoundScore(1);
      } else {
        player.incrementRoundScore(value);
      }
    }
  }
  std::vector<int> allPlayersTotalScores;
  std::vector<int> allPlayersRoundScores;
  for (auto &&player : players) {
    allPlayersTotalScores.push_back(player.getTotalScore());
    allPlayersRoundScores.push_back(player.getRoundScore());
  }
  if (gui->endOfRoundDialog(allPlayersRoundScores, allPlayersTotalScores)) {
    startNewRound();
  }
}
