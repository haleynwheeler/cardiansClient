#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include "GameLogic/Card.hpp"
#include "imageInsert.h"
#include <wx/wx.h>

class playerCard : public wxPanel {
  Card *theCard;
  wxBoxSizer *cardSizer;
  wxBoxSizer *cardHorizontalSizer;
  imageInsert *bgImage;
  imageInsert *suitImage;
  void played(wxMouseEvent& event);

public:
  playerCard(wxWindow *parent, Card *theCards, wxSize size, int bgType);
  playerCard(wxWindow *parent, int direction, int bgType, wxSize size,
             bool fullCard = TRUE);
  playerCard(wxWindow *parent, int bgType, wxSize size, bool deckEmpty = FALSE);
  ~playerCard();
  Card getCard();
  void updateCard(Card newCard);
};

#endif
