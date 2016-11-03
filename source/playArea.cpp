#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>
#include <vector>

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  int cardWidth = 20;
  int cardHeight = 100;
  Card *dummyCard = new Card(HEARTS, TWO);
  int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  heightLeft -= 850;

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 4;

  theMainSizer = new wxBoxSizer(wxVERTICAL);

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  verticalfieldArea = new wxBoxSizer(wxVERTICAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  wxBitmapButton *Deck = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/upFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerCard *Discard = new playerCard(parent, dummyCard, wxSize(80, 120));

  playerCard *tcard = new playerCard(parent, dummyCard, wxSize(70, 100));
  yourHand->Add(tcard);
  for (int i = 1; i < 13; i++) {
    playerCard *card = new playerCard(parent, dummyCard, wxSize(70, 100));
    yourHand->Add(card);
    if (i > thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }

  wxBitmapButton *card2 = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../../res/leftFull.jpg", wxBITMAP_TYPE_JPEG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  playerOne->Add(card2);
  for (int i = 0; i < playerOneHandSize; i++) {
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
  for (int i = 0; i < playerTwoHandSize; i++) {
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
  for (int i = 0; i < playerThreeHandSize; i++) {
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

  lowerPortion->AddSpacer(100);
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(middlePortion);
  //  theMainSizer->AddSpacer(10);
  theMainSizer->Add(lowerPortion, wxCENTER);
  SetSizerAndFit(theMainSizer);
}

void playArea::setDrewCardFunction(std::function<void()> f) {
  humanDrewCard = f;
}

void playArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void playArea::playerZero(std::vector<Card> hand) {
  yourHand->Clear();
  yourHand->Layout();
  Card *temper = new Card(hand.at(0).getSuit(), hand.at(0).getValue());
  playerCard *tcard =
      new playerCard(this->GetParent(), temper, wxSize(70, 100));
  //  tcard->Bind(wxEVT_BUTTON, &CrazyEightsGame::OnButton, this);
  yourHand->Add(tcard);
  for (int i = 1; i < hand.size(); i++) {
    Card *temp = new Card(hand.at(i).getSuit(), hand.at(i).getValue());
    playerCard *card = new playerCard(this->GetParent(), temp, wxSize(70, 100));
    //     card->Bind(wxEVT_BUTTON, &CrazyEightsGame::OnButton, this);
    yourHand->Add(card);
  }
  yourHand->Layout();
}

void playArea::playerAi(int playerId, std::vector<Card> hand) {
  switch (playerId) {
  case 1:
    playerOne->Detach(1);
    playerOne->Layout();
    break;

  case 2:
    playerTwo->Detach(1);
    playerTwo->Layout();
    break;

  case 3:
    playerThree->Detach(1);
    playerThree->Layout();
    break;
  }
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {
  switch (playerId) {

  case 0:
    playerZero(hand);
    break;
  case 1:
  case 2:
  case 3:
    playerAi(playerId, hand);
    break;
  }
  fieldArea->Detach(1);
  Card *tempest =
      new Card(topOfDiscardPile.getSuit(), topOfDiscardPile.getValue());
  playerCard *Discard =
      new playerCard(this->GetParent(), tempest, wxSize(80, 120));
  fieldArea->Add(Discard);
  fieldArea->Layout();
  if (deckEmpty) {
    wxBitmapButton *Deck = new wxBitmapButton(
        this, wxID_ANY, wxBitmap("../../res/white.jpg", wxBITMAP_TYPE_JPEG),
        wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator,
        wxButtonNameStr);
  }
}

void playArea::invalidMoveDialog() {
  wxMessageDialog dialog(NULL, "You played an invalid card. You must match "
                               "either the suit or the value of the card at "
                               "the top of the discard pile. Please try again.",
                         "Invalid Move", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

Suit playArea::userPickSuitDialog() {
  wxArrayString choices;
  choices.Add("Hearts");
  choices.Add("Spades");
  choices.Add("Clubs");
  choices.Add("Diamonds");
  wxString title("Pick a Suit");
  wxSingleChoiceDialog dialog(NULL, title, title, choices);
  dialog.ShowModal();
  int choice = dialog.GetSelection();
  return static_cast<Suit>(choice);
}

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

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
