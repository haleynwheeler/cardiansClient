#ifndef heartsArea_H
#define heartsArea_H

#include "GameLogic/Card.hpp"
#include "playerCard.h"
#include <functional>
#include <string>
#include <vector>
#include <wx/wx.h>

class heartsArea : public wxPanel {
  int thePlayerHandSize;
  int playerOneHandSize;
  int playerTwoHandSize;
  int playerThreeHandSize;
  wxBoxSizer *theMainSizer;

  wxBoxSizer *upperPortion;
  wxBoxSizer *middlePortion;
  wxBoxSizer *lowerPortion;

  wxBoxSizer *fieldArea;      // Horizontal 3 sections
  wxBoxSizer *leftFieldArea;  // Vertical 3 sections
  wxBoxSizer *midFieldArea;   // Verical 3 sections
  wxBoxSizer *rightFieldArea; // Vertical 3 sections

  wxBoxSizer *yourHand;
  wxBoxSizer *playerOne;
  wxBoxSizer *playerTwo;
  wxBoxSizer *playerThree;

  playerCard *playerZeroChoice;
  playerCard *playerOneChoice;
  playerCard *playerTwoChoice;
  playerCard *playerThreeChoice;
  std::vector<playerCard *> handCards;

  std::function<void(Card)> humanMadeMove;

public:
  heartsArea(wxFrame *parent);
  ~heartsArea();
  void updatePlayArea(int playerId, std::vector<Card> hand);

  void playerZero(std::vector<Card> hand);
  void playerAi(int playerId, std::vector<Card> hand);

  void invalidMoveDialog();
  bool endOfRoundDialog(std::vector<int> allPlayersRoundScores,
                        std::vector<int> allPlayersTotalScores);
  void setMadeMoveFunction(std::function<void(Card)>);
};

#endif
