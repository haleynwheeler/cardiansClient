#ifndef playArea_H
#define playArea_H

#include "GameLogic/Card.hpp"
#include "playerCard.h"
#include <functional>
#include <string>
#include <vector>
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

  playerCard *Deck;
  playerCard *Discard;
  std::vector<playerCard *> handCards;

  std::function<void()> humanDrewCard;
  std::function<void(Card)> humanMadeMove;

public:
  playArea(wxFrame *parent);
  ~playArea();
  void OnClick(wxCommandEvent &event);
  void updatePlayArea(int playerId, std::vector<Card> hand, bool deckEmpty,
                      Card topOfDiscardPile);

  void playerZero(std::vector<Card> hand);
  void playerAi(int playerId, std::vector<Card> hand);

  void invalidMoveDialog();
  Suit userPickSuitDialog();
  void aiPickedSuitDialog(Suit suitSpecified);
  bool endOfRoundDialog(std::vector<int> allPlayersRoundScores,
                        std::vector<int> allPlayersTotalScores);

  void setDrewCardFunction(std::function<void()>);
  void setMadeMoveFunction(std::function<void(Card)>);

  void getCardPlayed(wxMouseEvent &event);
  void getDeckCard(wxMouseEvent &event);
  enum { CARD_TOUCHED = 5, DECK_TOUHED = 15 };
  // wxDECLARE_EVENT_TABLE();
};

#endif
