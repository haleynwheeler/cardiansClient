#include "HeartsGame.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <wx/wx.h>

using namespace std::chrono_literals;
// constructor
HeartsGame::HeartsGame(wxFrame *mainFrame) : Game() {
  gui = new heartsArea(mainFrame);
  gui->setMadeMoveFunction([this](Card c) { humanMadeMove(c); });
  roundNumber = 0;
  cardsToPass.resize(4);
  // startNewRound();
}

void HeartsGame::startNewRound() {
  std::cout << "Starting a new round" << std::endl;
  roundNumber++;
  brokenHearts = false;
  tricksAssigned = 0;
  for (auto &&card : centerPile) {
    card = Card();
  }
  std::vector<Card> deck = initializeDeck();
  for (auto &&player : players) {
    player.startNewRound();
    player.initializeHand(deck, 13);
  }
  gui->initializePlayArea(players[0].getHand());
  setCardsAiWillPass();
  std::vector<Card> passed = gui->requestCardsPassed(players[0].getHand());
  humanPassedCards(passed);
}

void HeartsGame::startNewTrick(int startingPlayer) {
  playerLeadingTrick = startingPlayer;
  turn = startingPlayer;
  for (auto &&card : centerPile) {
    card = Card();
  }
  gui->updatePlayArea(turn, players[turn].getHand(), centerPile);
  if (turn > 0) {
    computersTurn();
  }
}

void HeartsGame::setCardsAiWillPass() {
  for (int i = 1; i < players.size(); i++) {
    // TODO: Write AI to pick cards to pass
    auto hand = players[i].getHand();
    for (int j = 0; j < 3; j++) {
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
  for (int i = 0; i < players.size(); i++) {
    Card card1 = cardsToPass[(i + roundNumber + 1) % players.size()][0];
    Card card2 = cardsToPass[(i + roundNumber + 1) % players.size()][1];
    Card card3 = cardsToPass[(i + roundNumber + 1) % players.size()][2];
    players[i].insertCardToHand(card1);
    players[i].insertCardToHand(card2);
    players[i].insertCardToHand(card3);
    std::cout << "Player " << i << " has " << players[i].getHand().size()
              << " cards" << std::endl;
  }
  gui->initializePlayArea(players[0].getHand());
  cardsToPass.clear();
  turn = findTwoOfClubs();
  startNewTrick(turn);
}

void HeartsGame::humanMadeMove(Card c) {
  if (turn == 0 && centerPile[0].getSuit() == UNDEFINED) {
    bool valid = checkCardValidity(c);
    if (valid) {
      players[0].removeCardFromHand(c);
      centerPile[0] = c;
      turn++;
      gui->updatePlayArea(0, players[0].getHand(), centerPile);
      computersTurn();
    } else {
      gui->invalidMoveDialog();
      return;
    }
  }
}

void HeartsGame::computersTurn() {
  int startLocation = turn;
  for (int i = startLocation; i < 4; i++) {
    if (centerPile[i].getSuit() == UNDEFINED) {
      turn = i;
      std::cout << "It's AI " << i << "'s turn" << std::endl;
      computersMove();
      gui->updatePlayArea(turn, players[turn].getHand(), centerPile);
      std::this_thread::sleep_for(1s);
    } else {
      assignTrick();
      return;
    }
  }
  if (centerPile[0].getSuit() == UNDEFINED) {
    turn = 0;
    std::cout << "It's the human's turn" << std::endl;
  } else {
    assignTrick();
    return;
  }
}

void HeartsGame::computersMove() {
  auto hand = players[turn].getHand();
  for (auto &&card : hand) {
    if (checkCardValidity(card)) {
      players[turn].removeCardFromHand(card);
      centerPile[turn] = card;
      std::cout << "AI " << turn << " played a " << card.getValue() << " of "
                << card.getSuit() << std::endl;
      return;
    }
  }
  std::cout << "computer did not have a valid move" << std::endl;
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
  std::cout << "I'm the lead player!" << std::endl;
  if (tricksAssigned == 0 && (c.getSuit() != CLUBS || c.getValue() != 2)) {
    std::cout << "First play of first round" << std::endl;
    return false;
  } else {
    std::cout << "Checking Card " << c.getValue() << " of " << c.getSuit()
              << std::endl;
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
  auto doesntHaveLeadSuit = noLeadSuit(leadSuit);
  // Check they didn't play a heart, queen of spades on first turn
  if (tricksAssigned == 0 && doesntHaveLeadSuit) {
    if (thisSuit == HEARTS || thisSuit == SPADES && c.getValue() == QUEEN) {
      return false;
    }
  }

  if (leadSuit == thisSuit) {
    return true;
  } else if (!doesntHaveLeadSuit && thisSuit != leadSuit) {
    return false;
  } else {
    if (thisSuit == HEARTS) {
      brokenHearts = true;
    }
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
      winningValue = centerPile[i].getValue();
    }
  }
  std::cout << "Player " << winner << " won the trick" << std::endl;
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

void HeartsGame::showScores() {
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

void HeartsGame::showGame() { gui->showGame(); }

void HeartsGame::hideGame() { gui->hideGame(); }

void HeartsGame::startGame() { startNewRound(); }
