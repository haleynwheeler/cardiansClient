#include "playerCard.h"
#include "baseBackground.h"
#include "playArea.h"

playerCard::playerCard(wxWindow *parent, int direction, int bgType, wxSize size,
                       bool fullCard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {
  background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath;
  if (fullCard) {
    bgImagePath =
        wxString::Format(wxT("../res/CardBacks/%i/%i.png"), bgType, direction);
  } else {
    bgImagePath =
        wxString::Format(wxT("../res/CardBacks/%i/%iS.png"), bgType, direction);
  }
  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);
  this->SetSizerAndFit(background);
}

playerCard::playerCard(wxWindow *parent, int bgType, wxSize size,
                       bool deckEmpty)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {

  background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath;
  if (deckEmpty) {
    bgImagePath = wxString::Format(wxT("../res/CardBacks/%i/0.png"), bgType);
  } else {
    bgImagePath = wxString::Format(wxT("../res/CardBacks/%i/1.png"), bgType);
  }
  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);
  this->SetSizerAndFit(background);
}

playerCard::playerCard(wxWindow *parent, Card *theCards, wxSize size,
                       int bgType)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {

  theCard = new Card(theCards->getSuit(), theCards->getValue());

  background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath =
      wxString::Format(wxT("../res/CardFaces/%i_of_%i.png"),
                       theCard->getValue(), theCard->getSuit());
  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);

  cardSizer = new wxBoxSizer(wxVERTICAL);
  cardHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
  cardSizer->SetMinSize(size);
  cardSizer->AddSpacer(10);

  this->SetSizerAndFit(cardSizer);
}

playerCard::~playerCard() {}

Card playerCard::getCard() {
  return Card(theCard->getSuit(), theCard->getValue());
}

void playerCard::setDrewCardFunction(std::function<void()> humanDrewCard) {
  bgImage->Bind(wxEVT_LEFT_UP,
                [=](wxMouseEvent &event) {
                  std::cout << "Human Drew Card" << std::endl;
                  humanDrewCard();
                },
                wxID_ANY);
}

void playerCard::setMoveFunction(std::function<void(Card)> humanMadeMove) {
  bgImage->Bind(wxEVT_LEFT_UP,
                [=](wxMouseEvent &event) {
                  std::cout << "Played Card" << theCard->getSuit() << " "
                            << theCard->getValue() << std::endl;
                  humanMadeMove(Card(theCard->getSuit(), theCard->getValue()));
                },
                wxID_ANY);
}

void playerCard::updateCard(Card c) {
  theCard = new Card(c.getSuit(), c.getValue());
  wxString bgImagePath =
      wxString::Format(wxT("../res/CardFaces/%i_of_%i.png"),
                       theCard->getValue(), theCard->getSuit());
  bgImage =
      new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                      this->GetSize().GetHeight(), this->GetSize().GetWidth());
  background->Clear(true);
  background->Add(bgImage);
  Update();
  Refresh();
}
