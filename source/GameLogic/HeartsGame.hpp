#ifndef HEARTS_GAME_HPP
#define HEARTS_GAME_HPP

#include "../heartsArea.h"
#include "Game.hpp"

class HeartsGame : public Game {
public:
  HeartsGame(wxFrame *);
  heartsArea *getGui() { return gui; };
  void showGame();
  void hideGame();

private:
  heartsArea *gui;
  int playerLeadingTrick;
  int roundNumber;
  bool brokenHearts = false;
  int tricksAssigned;
  std::array<Card, 4> centerPile;
  std::vector<std::vector<Card>> cardsToPass;
  void startNewRound();
  void startNewTrick(int);
  void setCardsAiWillPass();
  void humanPassedCards(std::vector<Card>);
  void passCards();
  void humanMadeMove(Card);
  void computersTurn();
  void computersMove();
  int findTwoOfClubs();
  bool allHearts();
  bool noLeadSuit(Suit s); // sees if hand holds lead suit
  bool checkCardValidity(Card);
  bool checkLeadPlayersCard(Card);
  bool checkFollowingPlayersCard(Card);
  void assignTrick();
  void assignPoints(int);
  void endRound();
  void showScores();
  // bool setPassCards(std::vector<Card> cards, std::string name);
  // void passCards(int round);
  int endTurn(int currentPlayer);
};

#endif // HEARTS_GAME_HPP
