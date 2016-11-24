#include "CrazyEightsGame.hpp"
#include <chrono>
#include <random>
#include <thread>
#include <wx/wx.h>

using namespace std::chrono_literals;

CrazyEightsGame::CrazyEightsGame(wxFrame *mainFrame) : Game() {
  gui = new playArea(mainFrame);
  gui->setMadeMoveFunction([this](Card c) { humanMadeMove(c); });
  gui->setDrewCardFunction([this]() { humanDrewCard(); });
  std::cout << "Created Play Area" << std::endl;
  startNewRound(true);
}

void CrazyEightsGame::startNewRound(bool newGame) {
  roundOver = false;
  turn = 0;
  deck = initializeDeck();
  for (auto &&player : players) {
    if (newGame) {
      player.startNewGame();
    } else {
      player.startNewRound();
    }
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
  gui->initializePlayArea(players[0].getHand(), topOfDiscardPile);
  std::cout << "Started New Round" << std::endl;
}

// THIS SHOULD BE CALLED WHEN THE DECK IS PRESSED
void CrazyEightsGame::humanDrewCard() {
  std::cout << "Human Drew Card" << std::endl;
  if (turn == 0 && !roundOver) {
    if (!deck.empty()) {
      players[0].insertCardToHand(deck.back());
      deck.pop_back();
      gui->updatePlayArea(0, players[0].getHand(), deck.empty(),
                          discardPile.back());
    } else {
      std::cout << "You passed" << std::endl;
      auto hand = players[0].getHand();
      for (auto &&card : hand) {
        auto validMove = checkCardValidity(card);
        if (validMove) {
          gui->invalidMoveDialog();
          return;
        }
      }
      gui->updatePlayArea(0, players[0].getHand(), deck.empty(),
                          discardPile.back());
      computersTurn();
    }
  }
}

// THIS SHOULD BE CALLED WHEN A CARD IN THE HAND IS PRESSED
void CrazyEightsGame::humanMadeMove(Card c) {
  std::cout << "Human Made Move" << std::endl;
  if (turn == 0 && !roundOver) {
    bool validMove = false;
    if (c.getValue() == EIGHT) {
      validMove = true;
      suitSpecified = gui->userPickSuitDialog();
      if (suitSpecified == UNDEFINED) {
        return;
      }
      removeCardFromHand(c);
    } else {
      validMove = checkCardValidity(c) && removeCardFromHand(c);
    }
    if (validMove) {
      if (players[0].getHand().size() == 0) {
        endRound();
        return;
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
    if (roundOver) {
      endRound();
      return;
    }
    gui->updatePlayArea(turn, players[turn].getHand(), deck.empty(),
                        discardPile.back());
    gui->Refresh();
    gui->Update();
    std::this_thread::sleep_for(1s);
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
    std::cout << "Drew new card" << std::endl;
    auto newCard = deck.back();
    deck.pop_back();
    players[turn].insertCardToHand(newCard);
    gui->updatePlayArea(turn, players[turn].getHand(), deck.empty(),
                        discardPile.back());
    gui->Refresh();
    gui->Update();
    std::this_thread::sleep_for(500ms);
    auto validMove = checkCardValidity(newCard);
    if (validMove) {
      performValidAiMove(newCard);
      return;
    }
  }
}

void CrazyEightsGame::performValidAiMove(Card card) {
  players[turn].removeCardFromHand(card);
  discardPile.push_back(card);
  if (players[turn].getHand().size() == 0) {
    roundOver = true;
    return;
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
  // Calculate Scores
  roundOver = true;
  bool gameOver = false;
  gui->updatePlayArea(turn, players[turn].getHand(), deck.empty(),
                      discardPile.back());
  gui->Refresh();
  gui->Update();
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
  showScores();
}

void CrazyEightsGame::showScores() {
  bool winner = false;
  std::vector<int> allPlayersTotalScores;
  std::vector<int> allPlayersRoundScores;
  for (auto &&player : players) {
    auto totalScore = player.getTotalScore();
    if (totalScore > 200) {
      winner = true;
    }
    allPlayersTotalScores.push_back(totalScore);
    allPlayersRoundScores.push_back(player.getRoundScore());
  }
  if (winner) {
    if (gui->endOfGameDialog(allPlayersRoundScores, allPlayersTotalScores)) {
      startNewRound(true);
    }
  } else {
    if (gui->endOfRoundDialog(allPlayersRoundScores, allPlayersTotalScores)) {
      startNewRound(false);
    }
  }
}

void CrazyEightsGame::showGame() { gui->Show(true); }

void CrazyEightsGame::hideGame() {
  std::cout << "This is pointer" << gui << std::endl;
}
