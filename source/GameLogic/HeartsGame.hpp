#ifndef HEARTS_GAME_HPP
#define HEARTS_GAME_HPP

#include "../clientInfo.h"
#include "../heartsArea.h"
#include "Game.hpp"

class HeartsGame : public Game {
public:
  HeartsGame(wxFrame *, clientInfo *client);
  heartsArea *getGui() { return gui; };
  void showGame();
  void hideGame();
  void startGame();
  void updateGui();

private:
  heartsArea *gui;
  int playerLeadingTrick;
  int roundNumber;
  bool brokenHearts = false;
  int tricksAssigned;
  std::array<Card, 4> centerPile;
  std::vector<std::vector<Card>> cardsToPass;
  void startNewRound(bool);
  void startNewTrick(int);
  void setCardsAiWillPass();
  void humanPassedCards(std::vector<Card>);
  void passCards();
  void humanMadeMove(Card);
  void computersTurn();
  void computersMove();
  int findTwoOfClubs();
  bool allHearts();
  void checkBrokenHearts(Card c);
  bool noLeadSuit(Suit s);
  bool checkCardValidity(Card);
  bool checkLeadPlayersCard(Card);
  bool checkFollowingPlayersCard(Card);
  void assignTrick();
  void assignPoints(int);
  void endRound();
  void showScores();
  int endTurn(int currentPlayer);
};

#endif // HEARTS_GAME_HPP
