/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/
#include "../clientInfo.h"
#include "../playArea.h"
#include "Card.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <vector>

class CrazyEightsGame : public Game {
private:
  playArea *gui;
  std::vector<Card> discardPile;
  std::vector<Card> deck;
  Suit suitSpecified;
  bool roundOver;
  void computersTurn();
  bool checkCardValidity(Card);
  bool removeCardFromHand(Card);
  void endRound();
  void computersMove();
  void performValidAiMove(Card);
  void humanMadeMove(Card);
  void humanDrewCard();
  void displayEndOfRoundDialogBox();
  void showScores();
  void updateGui();

public:
  CrazyEightsGame(wxFrame *, clientInfo *client);
  void startNewRound(bool newGame);
  playArea *getGui() { return gui; };
  void showGame();
  void hideGame();
};
