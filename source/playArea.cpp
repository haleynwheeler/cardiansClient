#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  int cardWidth = 20;
  int cardHeight = 100;
  Card *dummyCard = new Card(HEARTS, TWO);
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
      this, wxID_ANY, wxBitmap("../../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  wxBitmapButton *Deck = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    wxBitmapButton *Discard = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/white.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

  playerCard *tcard = new playerCard(parent,dummyCard,wxSize(60,100));
  yourHand->Add(tcard);
  yourHand->AddSpacer(10);
  for (int i = 0; i < 4; i++) {
    playerCard *card = new playerCard(parent,dummyCard,wxSize(20,100));
    yourHand->Add(card);
    yourHand->AddSpacer(5);
  }

  wxBitmapButton *card2 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/leftFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerOne->Add(card2);
  for (int i = 0; i < 4; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("../../res/left.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    playerOne->Add(card);
  }

  wxBitmapButton *card3 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerTwo->Add(card3);
  for (int i = 0; i < 4; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("../../res/down.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
    playerTwo->Add(card);
  }

  wxBitmapButton *card4 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/rightFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerThree->Add(card4);
  for (int i = 0; i < 4; i++) {
    wxBitmapButton *card = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("../../res/right.jpg", wxBITMAP_TYPE_JPEG),
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
//  theMainSizer->AddSpacer(10);
  theMainSizer->Add(lowerPortion, wxCENTER);
  SetSizerAndFit(theMainSizer);
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {


                              }

void playArea::invalidMoveDialog() {
  wxMessageDialog dialog(NULL, "You played an invalid card. You must match "
                               "either the suit or the value of the card at "
                               "the top of the discard pile. Please try again.",
                         "Invalid Move", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

Suit playArea::userPickSuitDialog() { return HEARTS; }

void playArea::aiPickedSuitDialog(Suit suitSpecified) {
  std::string msg = "The computer played an eight and have chosen the suit ";
  if (suitSpecified == HEARTS) {
    msg += "hearts.";
  } else if (suitSpecified == SPADES) {
    msg += "spades.";
  } else if (suitSpecified == CLUBS) {
    msg += "clubs.";
  } else {
    msg += "diamonds.";
  }
  wxMessageDialog dialog(NULL, msg, "Computer Played an Eight");
  dialog.ShowModal();
}

bool playArea::endOfRoundDialog(std::vector<int> playersRoundScores,
                                std::vector<int> playersOverallScores) {
  std::string msg = "The round is over. Would you like to play again?\n\n";
  msg += "SCORES:\n";
  msg += "YOU:\t";
  msg += "Round Score: " + std::to_string(playersRoundScores[0]) + "\n";
  msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[0]);

  for (int i = 1; i < 4; i++) {
    msg += "\nAI " + std::to_string(i) + ":\t";
    msg += "Round Score: " + std::to_string(playersRoundScores[i]) + "\n";
    msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[i]);
  }

  wxMessageDialog dialog(NULL, msg, "Round Over", wxYES_NO);
  auto decision = dialog.ShowModal();
  if (decision == wxID_YES) {
    return true;
  } else {
    return false;
  }
}

playArea::~playArea() {}

// BEGIN_EVENT_TABLE(playArea,wxPanel)
//   EVT_BUTTON()
// END_EVENT_TABLE()

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
