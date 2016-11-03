#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include <wx/wx.h>
#include "crazyEightsLogic/Card.hpp"

class playerCard : public wxPanel {
  Card *theCard;
public:
  playerCard(wxFrame* parent, Card theCards);
  ~playerCard();
  Card getCard();

};

#endif
