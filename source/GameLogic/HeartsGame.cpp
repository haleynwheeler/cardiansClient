#include "HeartsGame.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <wx/wx.h>

using namespace std::chrono_literals;
// constructor
HeartsGame::HeartsGame(wxFrame *mainFrame) : Game(mainFrame) {
  roundNumber = 0;
  cardsToPass.resize(4);
  startNewRound();
}

void HeartsGame::startNewRound() {
  roundNumber++;
  brokenHearts = false;
  tricksAssigned = 0;
  std::vector<Card> deck = initializeDeck();
  for (auto &&player : players) {
    player.startNewRound();
    player.initializeHand(deck, 13);
  }
  setCardsAiWillPass();
}

void HeartsGame::startNewTrick(int startingPlayer) {
  playerLeadingTrick = startingPlayer;
  turn = startingPlayer;
  for (auto &&card : centerPile) {
    card = Card();
  }
  if (turn > 0) {
    computersTurn();
  }
}

void HeartsGame::setCardsAiWillPass() {
  for (int i = 1; i < players.size(); i++) {
    // TODO: Write AI to pick cards to pass
    auto hand = players[i].getHand();
    for (int j = 0; j < 4; j++) {
      cardsToPass[i].push_back(hand[j]);
      players[i].removeCardFromHand(hand[j]);
    }
  }
}

void HeartsGame::humanPassedCards(std::vector<Card> passedCards) {
  for (auto &&card : passedCards) {
    cardsToPass[0].push_back(card);
    players[0].removeCardFromHand(card);
  }
  passCards();
}

// function for passing cards at beginning of round
void HeartsGame::passCards() {
  for (size_t i = 0; i < players.size(); i++) {
    Card card1 = cardsToPass[(i + roundNumber + 1) % players.size()][0];
    Card card2 = cardsToPass[(i + roundNumber + 1) % players.size()][1];
    Card card3 = cardsToPass[(i + roundNumber + 1) % players.size()][2];
    players[i].insertCardToHand(card1);
    players[i].insertCardToHand(card2);
    players[i].insertCardToHand(card3);
  }
  // gui->updatePlayArea();
  gui->Refresh();
  gui->Update();
  cardsToPass.clear();
  turn = findTwoOfClubs();
  startNewTrick(turn);
}

void HeartsGame::humanMadeMove(Card c) {}

void HeartsGame::computersTurn() {
  for (int i = turn; i < 4; i++) {
    if (centerPile[0].getSuit() == UNDEFINED) {
      computersMove();
      // gui->updatePlayArea();
      gui->Refresh();
      gui->Update();
      std::this_thread::sleep_for(2s);
    } else {
      assignTrick();
    }
  }
  if (centerPile[0].getSuit() == UNDEFINED) {
    turn = 0;
  } else {
    assignTrick();
  }
}

void HeartsGame::computersMove() {
  auto hand = players[turn].getHand();
  for (auto &&card : hand) {
    if (checkCardValidity(card)) {
      players[turn].removeCardFromHand(card);
      centerPile[turn] = card;
    }
  }
}

// looks through each hand to find the 2 of clubs
// returns the index of the player with the 2 of clubs
int HeartsGame::findTwoOfClubs() {
  for (int i = 0; i < players.size(); ++i) {
    std::vector<Card> temp = players[i].getHand();
    for (auto j = 0; j < 13; ++j) {
      if (temp[j].getSuit() == CLUBS && temp[j].getValue() == 2) {
        return i;
      }
    }
  }
  return -1;
}

// checks to see if a players hand is all hearts.
// takes a vector of cards, ie the player's hand
// returns a bool of whether all the cards are hearts
bool HeartsGame::allHearts() {
  auto hand = players[turn].getHand();
  for (auto &&card : hand) {
    if (card.getSuit() != HEARTS) {
      return false;
    }
  }
  return true;
}

// compares hand against the lead suit
// Takes in a suit and the player's hand
// returns a bool whether there is a card with suit s
// in the hand
bool HeartsGame::noLeadSuit(Suit s) {
  auto hand = players[turn].getHand();
  for (auto &&card : hand) {
    if (card.getSuit() == s) {
      return false;
    }
  }
  return true;
}

bool HeartsGame::checkCardValidity(Card c) {
  if (playerLeadingTrick == turn) {
    return checkLeadPlayersCard(c);
  } else {
    return checkFollowingPlayersCard(c);
  }
}

bool HeartsGame::checkLeadPlayersCard(Card c) {
  if (tricksAssigned == 0 && c.getSuit() != CLUBS || c.getValue() != 2) {
    return false;
  } else {
    if (c.getSuit() != HEARTS) {
      return true;
    } else {
      if (brokenHearts || allHearts()) {
        brokenHearts = true;
        return true;
      }
      return false;
    }
  }
}

bool HeartsGame::checkFollowingPlayersCard(Card c) {
  auto leadSuit = centerPile[playerLeadingTrick].getSuit();
  auto thisSuit = c.getSuit();

  // Check they didn't play a heart, queen of spades on first turn
  if (tricksAssigned == 0 && noLeadSuit(leadSuit)) {
    if (thisSuit == HEARTS || thisSuit == SPADES && c.getValue() == QUEEN) {
      return false;
    }
  }

  if (leadSuit == thisSuit) {
    return true;
  } else if (thisSuit != leadSuit && noLeadSuit(leadSuit)) {
    if (thisSuit == HEARTS) {
      brokenHearts = true;
    }
    return true;
  } else {
    return true;
  }
}

void HeartsGame::assignTrick() {
  tricksAssigned++;
  Suit leadSuit = centerPile[playerLeadingTrick].getSuit();
  int winningValue = -1;
  int winner = -1;
  for (int i = 0; i < centerPile.size(); i++) {
    if (centerPile[i].getSuit() == leadSuit &&
        centerPile[i].getValue() > winningValue) {
      winner = i;
    }
  }
  assignPoints(winner);
  if (tricksAssigned < 13) {
    startNewTrick(winner);
  } else {
    endRound();
  }
}

void HeartsGame::assignPoints(int i) {
  for (auto &&card : centerPile) {
    if (card.getSuit() == HEARTS) {
      players[i].incrementRoundScore(1);
    } else if (card.getSuit() == SPADES && card.getValue() == QUEEN) {
      players[i].incrementRoundScore(13);
    }
  }
}

void HeartsGame::endRound() {
  for (int i = 0; i < players.size(); i++) {
    if (players[i].getRoundScore() == 26) {
      players[(i + 1) % 4].setRoundScore(26);
      players[(i + 2) % 4].setRoundScore(26);
      players[(i + 3) % 4].setRoundScore(26);
      break;
    }
  }
  showScores();
}

// checks to see if a move is valid
// takes index of player in vector, the proposed card,
// the trick number, and the turn number
// returns a bool of whether the card is a valid move
// bool HeartsGame::checkCardValidity(Card move, int turn) {
//   Suit lead;
//   if (centerPile.size() > 0)
//     lead = centerPile[0].getSuit();
//   if (turn == 0) {
//     if (centerPile.size() == 0) {
//       if (move.getSuit() != CLUBS && move.getValue() != TWO)
//         return false;
//       else
//         return true;
//     } else {
//       if (move.getSuit() != lead && noLeadSuit(lead,
//       players[turn].getHand())) {
//         if (move.getSuit() == HEARTS && brokenHearts)
//           return true;
//         else if (move.getSuit() == HEARTS &&
//                  allhearts(players[turn].getHand())) {
//           brokenHearts = true;
//           return true;
//         } else if (move.getSuit() == HEARTS)
//           return false;
//         else
//           return true;
//       } else if (move.getSuit() != lead)
//         return false;
//       else
//         return true;
//     }
//   } else {
//     if (centerPile.size() == 0) {
//       if (move.getSuit() == HEARTS && allhearts(players[turn].getHand())) {
//         brokenHearts = true;
//         return true;
//       } else if (move.getSuit() == HEARTS && brokenHearts)
//         return true;
//       else if (move.getSuit() == HEARTS)
//         return false;
//       return true;
//     } else {
//       if (move.getSuit() != lead && noLeadSuit(lead,
//       players[turn].getHand())) {
//         if (move.getSuit() == HEARTS && brokenHearts)
//           return true;
//         else if (move.getSuit() == HEARTS &&
//                  allhearts(players[turn].getHand())) {
//           brokenHearts = true;
//           return true;
//         } else if (move.getSuit() == HEARTS)
//           return false;
//         else
//           return true;
//       } else if (move.getSuit() != lead)
//         return false;
//       else
//         return true;
//     }
//   }
//   return false;
// }

// finished the turn
// takes the index of the current player
// returns the player index who won the trick
// int HeartsGame::endTurn(int currentPlayer) {
//   Suit leadSuit = centerPile[0].getSuit();
//   int maxIndex = 0;
//   int maxValue = 0;
//   int score = 0;
//   for (int i = 0; i < centerPile.size(); i++) {
//     Card tmp = centerPile[i];
//     if (tmp.getSuit() == leadSuit && tmp.getValue() > maxValue) {
//       maxValue = tmp.getValue();
//       maxIndex = i;
//     }
//     if (tmp.getSuit() == SPADES && tmp.getValue() == 11)
//       score += 13;
//     if (tmp.getSuit() == HEARTS)
//       score++;
//   }
//   players[(maxIndex + currentPlayer) % players.size()].incrementRoundScore(
//       score);
//   centerPile.clear();
//   return (maxIndex + currentPlayer) % players.size();
// }
//
// // finishes the round and applies scores

// passes a card
// takes a card and index of player
// void HeartsGame::passCard(Card tmp, int i) { cardsToPass[i].push_back(tmp); }
