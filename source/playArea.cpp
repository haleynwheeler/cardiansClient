#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  int cardWidth = 20;
  int cardHeight = 100;

  int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  heightLeft -= 850;

  wxBoxSizer *theMainSizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *upperPortion = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *middlePortion = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *fieldArea = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *verticalfieldArea = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *yourHand = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerOne = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *playerTwo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerThree = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  wxBitmapButton *Deck = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  wxBitmapButton *Discard = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("white.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

  wxString upFull = wxT("downFull.jpg");
  wxBitmapButton *card1 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap(upFull, wxBITMAP_TYPE_JPEG), wxDefaultPosition,
      wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  yourHand->Add(card1);
  for (int i = 0; i < 12; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("up.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    // card->Bind(wxEVT_BUTTON, &playArea::OnClick, this);
    yourHand->Add(card);
  }

  wxBitmapButton *card2 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("leftFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerOne->Add(card2);
  for (int i = 0; i < 12; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("left.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    playerOne->Add(card);
  }

  wxBitmapButton *card3 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerTwo->Add(card3);
  for (int i = 0; i < 12; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("down.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    playerTwo->Add(card);
  }

  wxBitmapButton *card4 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("rightFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerThree->Add(card4);
  for (int i = 0; i < 12; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("right.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    playerThree->Add(card);
  }

  fieldArea->Add(Deck);
  fieldArea->Add(Discard);

  verticalfieldArea->AddSpacer(180);
  verticalfieldArea->Add(fieldArea);
  verticalfieldArea->AddSpacer(180);

  upperPortion->Add(topLogo);
  upperPortion->AddSpacer(20);
  upperPortion->Add(playerTwo, wxALIGN_CENTRE_VERTICAL);
  upperPortion->AddSpacer(80);

  middlePortion->AddSpacer(20);
  middlePortion->Add(playerOne, wxCENTER);
  middlePortion->AddSpacer(270);
  middlePortion->Add(verticalfieldArea);
  middlePortion->AddSpacer(270);
  middlePortion->Add(playerThree, wxCENTER);

  lowerPortion->AddSpacer(270);
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(middlePortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(lowerPortion, wxCENTER);
  SetSizerAndFit(theMainSizer);
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {}

void playArea::invalidMoveDialog() {}

Suit playArea::userPickSuitDialog() { return HEARTS; }

void playArea::aiPickedSuitDialog(Suit suitSpecified) {}

bool playArea::endOfRoundDialog(std::vector<int> allPlayersRoundScores,
                                std::vector<int> allPlayersTotalScores) {
  return false;
}

playArea::~playArea() {}

// BEGIN_EVENT_TABLE(playArea,wxPanel)
//   EVT_BUTTON()
// END_EVENT_TABLE()

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
