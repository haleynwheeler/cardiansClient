#include "Game.hpp"
#include <ctime>

CrazyEightsGame::CrazyEightsGame() {
  // Construct a Player Named "You". This will be our Human Player.
  players.push_back(Player(0, "You"));

  // Construct the AI Players.
  for (auto i = 1; i < 4; i++) {
    players.push_back(Player(0, "AI " + i));
  }
  startNewRound();
}

void CrazyEightsGame::startNewRound() {
  deck = initializeDeck();
  for (auto &&player : players) {
    player.startNewRound();
    player.initializeHand(deck, 5);
    discardPile.push_back(deck.back());
    deck.pop_back();
    turn = 0;
    updateGUI();
  }
}

// THIS SHOULD BE CALLED WHEN THE DECK IS PRESSED
void CrazyEightsGame::humanDrewCard() {
  if (turn == 0) {
    players[0].insertCardToHand(deck.back());
    deck.pop_back();
    updateGUI();
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
        suitSpecified = askUserToPickSuit();
      }
      updateGUI();
      computersTurn();
    } else {
      // TELL THEM THEY'VE PLAYED A BAD MOVE!
    }
  }
}

void CrazyEightsGame::computersTurn() {
  for (int i = 1; i < 4; i++) {
    turn = i;
    computersMove();
    updateGUI();
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
  while (true) {
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
    std::srand(std::time(0));
    suitSpecified = static_cast<Suit>(std::rand() % 3);
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
  displayEndOfRoundDialogBox();
}

void CrazyEightsGame::updateGUI() {
  // Updates the look of the GUI screen (after card is played or drawn)
}

Suit CrazyEightsGame::askUserToPickSuit() {
  // Prompts the user with a dialog box to pick a suit after playing an 8
  return HEARTS;
}

void CrazyEightsGame::displayEndOfRoundDialogBox() {
  // Displays the dialog box at the end of round
  // players[i].getOverallScores() will return a vector of all the previous
  // rounds scores
  // players[i].getRoundScore() will return the score of the round that just
  // ended
  // players[i].getTotalScore() will return the sum of all the scores (including
  // previous round)

  // If they press true, the function startNewRound() should be called.
}
