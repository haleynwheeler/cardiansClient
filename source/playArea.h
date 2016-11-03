#ifndef playArea_H
#define playArea_H

#include "crazyEightsLogic/Card.hpp"
#include"playerCard.h"
#include <string>
#include <wx/wx.h>

class playArea : public wxPanel {
  int thePlayerHandSize;
  int playerOneHandSize;
  int playerTwoHandSize;
  int playerThreeHandSize;
  wxBoxSizer *theMainSizer;

  wxBoxSizer *upperPortion;
  wxBoxSizer *middlePortion;
  wxBoxSizer *lowerPortion;

  wxBoxSizer *fieldArea;
  wxBoxSizer *verticalfieldArea;

  wxBoxSizer *yourHand;
  wxBoxSizer *playerOne;
  wxBoxSizer *playerTwo;
  wxBoxSizer *playerThree;

public:
  playArea(wxFrame *parent);
  ~playArea();
  void OnClick(wxCommandEvent &event);
  void updatePlayArea(int playerId, std::vector<Card> hand, bool deckEmpty,
                      Card topOfDiscardPile);

  void playerZero(std::vector<Card> hand,
                      bool deckEmpty, Card topOfDiscardPile);
  void playerAi(int playerId, std::vector<Card> hand,
                      bool deckEmpty, Card topOfDiscardPile);

  void invalidMoveDialog();
  Suit userPickSuitDialog();
  void aiPickedSuitDialog(Suit suitSpecified);
  bool endOfRoundDialog(std::vector<int> allPlayersRoundScores,
                        std::vector<int> allPlayersTotalScores);
};
#endif
