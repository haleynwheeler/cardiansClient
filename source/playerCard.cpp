#include "playerCard.h"
#include "baseBackground.h"
#include "playArea.h"

playerCard::playerCard(wxWindow *parent, int direction, int bgType, wxSize size,
                       bool fullCard)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxTAB_TRAVERSAL,
              wxPanelNameStr) {
  wxBoxSizer *background = new wxBoxSizer(wxHORIZONTAL);
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

  wxBoxSizer *background = new wxBoxSizer(wxHORIZONTAL);
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

  wxBoxSizer *background = new wxBoxSizer(wxHORIZONTAL);
  wxString bgImagePath =
      wxString::Format(wxT("../res/%i.png"), size.GetWidth());
  bgImage = new imageInsert(this, bgImagePath, wxBITMAP_TYPE_PNG,
                            size.GetHeight(), size.GetWidth());
  background->Add(bgImage);
  background->SetMinSize(size);
  // background->SetItemMinSize(0,size);

  cardSizer = new wxBoxSizer(wxVERTICAL);
  cardHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
  cardSizer->SetMinSize(size);
  cardSizer->AddSpacer(10);

  theCard = new Card(theCards->getSuit(), theCards->getValue());

  wxString suitPath =
      wxString::Format(wxT("../res/%i.png"), theCard->getSuit());
  imageInsert *suitImage =
      new imageInsert(this, suitPath, wxBITMAP_TYPE_PNG, 20, 20);

  wxString cardValue = wxString::Format(wxT("%i"), theCard->getValue());
  wxStaticText *cardFront =
      new wxStaticText(this, wxID_ANY, cardValue, wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE);
  wxFont font = cardFront->GetFont();
  font.SetPointSize(20);
  cardFront->SetFont(font);
  cardSizer->Add(suitImage);
  cardSizer->Add(cardFront, wxALIGN_CENTRE);

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
