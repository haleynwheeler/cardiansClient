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
  SetBackgroundColour(wxColour(120, 120, 20));
}

playerCard::playerCard(wxWindow *parent, int bgType, wxSize size,
                       bool deckEmpty)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {

  background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath;
  bgImagePath = wxString::Format(wxT("../res/CardBacks/%i/0.png"), bgType);
  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);
  SetSizerAndFit(background);
}

playerCard::playerCard(wxWindow *parent, Card *theCards, wxSize size,
                       int bgType, bool largeCard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {
  theCard = new Card(theCards->getSuit(), theCards->getValue());
  background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath;
  if (!largeCard) {
    bgImagePath = wxString::Format(wxT("../res/CardFaces/small/%i_of_%i.png"),
                                   theCard->getValue(), theCard->getSuit());
  } else {
    bgImagePath = wxString::Format(wxT("../res/CardFaces/%i_of_%i.png"),
                                   theCard->getValue(), theCard->getSuit());
  }

  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);
  cardSizer = new wxBoxSizer(wxVERTICAL);
  cardHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
  cardSizer->SetMinSize(size);
  // cardSizer->AddSpacer(10);
  this->SetSizerAndFit(cardSizer);
  Update();
  Refresh();
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

void playerCard::updateCard(Card c, bool largeSize) {
  theCard = new Card(c.getSuit(), c.getValue());
  wxString bgImagePath;
  if (!largeSize) {
    bgImagePath = wxString::Format(wxT("../res/CardFaces/small/%i_of_%i.png"),
                                   theCard->getValue(), theCard->getSuit());
  } else {
    bgImagePath = wxString::Format(wxT("../res/CardFaces/%i_of_%i.png"),
                                   theCard->getValue(), theCard->getSuit());
  }

  bgImage =
      new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                      this->GetSize().GetHeight(), this->GetSize().GetWidth());
  background->Clear(true);
  background->Add(bgImage);
  Update();
  Refresh();
}

void playerCard::updateDeck(bool deckEmpty, int bgType) {
  wxString bgImagePath;
  if (!deckEmpty) {
    bgImagePath = wxString::Format(wxT("../res/CardBacks/%i/1.png"), bgType);
  } else {
    bgImagePath = wxString::Format(wxT("../res/CardBacks/%i/0.png"), bgType);
  }
  std::cout << bgImagePath << std::endl;
  bgImage =
      new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                      this->GetSize().GetHeight(), this->GetSize().GetWidth());
  background->Clear(true);
  background->Add(bgImage);
  SetBackgroundColour(wxColour(100, 100, 100));
  Update();
}
