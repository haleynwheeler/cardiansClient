/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/
#include "Card.hpp"
#include "Player.hpp"
#include <vector>

class CrazyEightsGame {
private:
  std::vector<Card> deck;
  std::vector<Card> discardPile;
  std::vector<Player> players;
  std::vector<Card> field;
  int turn; // index in player vector
  Suit suitSpecified;
  void computersTurn();
  void humanDrewCard();     // Needs an action listener for when deck is pressed
  void humanMadeMove(Card); // Needs an action listener for when card is pressed
  Suit askUserToPickSuit(); // Shows a dialog box prompting user to pick a suit
                            // (used when an 8 is played)
  bool checkCardValidity(Card);
  bool removeCardFromHand(Card);
  void endRound();
  void displayEndOfRoundDialogBox(); // Shows a dialog box of Player's scores.
  void startNewRound();
  void computersMove();
  void performValidAiMove(Card);
  void updateGUI();

public:
  CrazyEightsGame();
};
