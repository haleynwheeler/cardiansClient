#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include <wx/wx.h>
#include "crazyEightsLogic/Card.hpp"
#include "imageInsert.h"

class playerCard : public wxPanel {
  Card *theCard;
  wxBoxSizer *cardSizer;
  wxBoxSizer *cardHorizontalSizer;
public:
  playerCard(wxWindow* parent, Card *theCards, wxSize size);
  playerCard(wxWindow* parent, int direction, int bgType, wxSize size, bool fullCard =TRUE);
  playerCard(wxWindow* parent, int bgType, wxSize size, bool deckEmpty =FALSE);
  ~playerCard();
  Card getCard();

  // wxDECLARE_EVENT_TABLE();
};

#endif


// EVT_BUTTON(loginButton, login::OnLogin)
// tcard->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
//        setMadeMoveFunction(this->getCard());
// });
