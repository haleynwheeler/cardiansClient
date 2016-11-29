#include "heartsArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>
#include <vector>

heartsArea::heartsArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  int cardWidth = 20;
  int cardHeight = 100;
  int cardBackType = 14;
  Card *dummyCard = new Card(HEARTS, TWO);

  int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  heightLeft -= 850;

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 13;

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  leftFieldArea = new wxBoxSizer(wxVERTICAL);
  midFieldArea = new wxBoxSizer(wxVERTICAL);
  rightFieldArea = new wxBoxSizer(wxVERTICAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);
  theMainSizer = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetLabel("topLogo");
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  for (int i = 0; i < 12; i++) {
    playerCard *card =
        new playerCard(this->GetParent(), dummyCard, wxSize(80, 120), 14);
    handCards.push_back(card);
    yourHand->Add(card);
    if (i >= thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }

  playerCard *card =
      new playerCard(this->GetParent(), 2, cardBackType, wxSize(100, 70));
  playerOne->Add(card);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
                                      wxSize(100, 20), false);
    playerOne->Add(card);
    if (i >= playerOneHandSize) {
      playerOne->Hide(i);
    }
  }

  playerCard *card1 =
      new playerCard(this->GetParent(), 3, cardBackType, wxSize(70, 100));
  playerTwo->Add(card1);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this->GetParent(), 3, cardBackType,
                                      wxSize(20, 100), false);
    playerTwo->Add(card);
    if (i >= playerTwoHandSize) {
      playerTwo->Hide(i);
    }
  }

  playerCard *card2 =
      new playerCard(this->GetParent(), 4, cardBackType, wxSize(100, 70));
  playerThree->Add(card2);
  for (int i = 0; i < 12; i++) {
    playerCard *card = new playerCard(this->GetParent(), 4, cardBackType,
                                      wxSize(100, 20), false);
    playerThree->Add(card);
    if (i >= playerThreeHandSize) {
      playerThree->Hide(i);
    }
  }

  playerZeroChoice =
      new playerCard(this->GetParent(), 1, cardBackType, wxSize(70, 100));
  playerOneChoice =
      new playerCard(this->GetParent(), 2, cardBackType, wxSize(100, 70));
  playerTwoChoice =
      new playerCard(this->GetParent(), 3, cardBackType, wxSize(70, 100));
  playerThreeChoice =
      new playerCard(this->GetParent(), 4, cardBackType, wxSize(100, 70));

  leftFieldArea->AddSpacer(180);
  leftFieldArea->Add(playerOneChoice, wxALIGN_LEFT);
  leftFieldArea->AddSpacer(180);

  midFieldArea->Add(playerTwoChoice);
  midFieldArea->AddSpacer(250);
  midFieldArea->Add(playerZeroChoice);
  midFieldArea->AddSpacer(10);

  rightFieldArea->AddSpacer(180);
  rightFieldArea->Add(playerThreeChoice, wxALIGN_RIGHT);
  rightFieldArea->AddSpacer(180);

  fieldArea->Add(leftFieldArea);
  fieldArea->AddSpacer(150);
  fieldArea->Add(midFieldArea);
  fieldArea->AddSpacer(150);
  fieldArea->Add(rightFieldArea);

  upperPortion->Add(topLogo);
  upperPortion->AddSpacer(20);
  upperPortion->Add(playerTwo, wxALIGN_CENTRE_VERTICAL);
  upperPortion->AddSpacer(80);

  middlePortion->AddSpacer(20);
  middlePortion->Add(playerOne, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(50);
  middlePortion->Add(fieldArea);
  middlePortion->AddSpacer(50);
  middlePortion->Add(playerThree, wxALIGN_BOTTOM);

  lowerPortion->AddSpacer(100);
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);
  SetSizerAndFit(theMainSizer);
}

void heartsArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void heartsArea::playerZero(std::vector<Card> hand) {
  yourHand->Clear(true);
  handCards.clear();
  for (auto &&handCard : hand) {
    Card *temp = new Card(handCard.getSuit(), handCard.getValue());
    playerCard *card =
        new playerCard(this->GetParent(), temp, wxSize(80, 120), 14);
    card->setMoveFunction(humanMadeMove);
    handCards.push_back(card);
    yourHand->Add(card);
  }
  yourHand->Layout();
  theMainSizer->Layout();
}

void heartsArea::playerAi(int playerId, std::vector<Card> hand) {
  switch (playerId) {
  case 1:
    playerOne->Show(this, false, true);
    playerOne->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= hand.size()) {
        playerOne->Hide(i);
      }
    }
    break;

  case 2:
    playerTwo->Show(this, false, true);
    playerTwo->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= hand.size()) {
        playerTwo->Hide(i);
      }
    }
    break;
    std::cout << handCards.at(0) << std::endl;
  case 3:
    playerThree->Show(this, false, true);
    playerThree->ShowItems(true);
    for (int i = 0; i < 13; i++) {
      if (i >= hand.size()) {
        playerThree->Hide(i);
      }
    }
    break;
  }
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
}

void heartsArea::initializePlayArea(std::vector<Card> hand) {
  std::cout << "initializePlayArea" << std::endl;
  int cardBackType = 14;
  playerZero(hand);
  playerAi(1, hand);
  playerAi(2, hand);
  playerAi(3, hand);
  // playerZeroChoice->Hide();
  // playerOneChoice->Hide();
  // playerTwoChoice->Hide();
  // playerThreeChoice->Hide();
  this->Refresh();
  this->Update();
}

void heartsArea::updatePlayArea(int playerId, std::vector<Card> hand,
                                std::array<Card, 4> centerPile) {
  std::cout << "Updating play area" << std::endl;
  if (playerId == 0) {
    playerZero(hand);
  } else {
    playerAi(playerId, hand);
  }
  updateMiddleCards(centerPile);
  theMainSizer->Layout();
  this->Refresh();
  this->Update();
}

void heartsArea::updateMiddleCards(std::array<Card, 4> centerPile) {
  if (centerPile[0].getSuit() == UNDEFINED) {
    playerZeroChoice->Hide();
    std::cout << "Hasn't played" << std::endl;
  } else {
    playerZeroChoice->Show();
    // Card *tempest = new Card(centerPile[0].getSuit(),
    // centerPile[0].getValue());
    // playerZeroChoice =
    // new playerCard(this->GetParent(), tempest, wxSize(70, 100), 14);
    playerZeroChoice->updateCard(centerPile[0]);
    playerZeroChoice->Layout();
  }

  if (centerPile[1].getSuit() == UNDEFINED) {
    playerOneChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerOneChoice->Show();
    playerOneChoice->updateCard(centerPile[1]);
    playerOneChoice->Layout();
  }

  if (centerPile[2].getSuit() == UNDEFINED) {
    playerTwoChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerTwoChoice->Show();
    playerTwoChoice->updateCard(centerPile[2]);
    playerTwoChoice->Layout();
  }

  if (centerPile[3].getSuit() == UNDEFINED) {
    playerThreeChoice->Hide();
    std::cout << "Hasn't played" << std::endl;

  } else {
    playerThreeChoice->Show();
    playerThreeChoice->updateCard(centerPile[3]);
    playerThreeChoice->Layout();
  }

  leftFieldArea->Layout();
  midFieldArea->Layout();
  rightFieldArea->Layout();
}

std::vector<Card> heartsArea::requestCardsPassed(std::vector<Card> hand) {
  wxArrayString choices;
  std::vector<Card> selection;
  for (auto &&card : hand) {
    std::string c = std::to_string(card.getValue()) + " of " +
                    std::to_string(card.getSuit());
    choices.Add(c);
  }
  wxString title("Pick 3 Cards to Pass");
  wxMultiChoiceDialog dialog(NULL, title, title, choices);
  auto yes = dialog.ShowModal();
  if (yes == wxID_OK) {
    auto choices = dialog.GetSelections();
    int numChoices = 0;
    for (auto &&c : choices) {
      std::cout << "Picked: " << hand[c].getValue() << " of "
                << hand[c].getSuit() << std::endl;
      selection.push_back(hand[c]);
      numChoices++;
    }
    if (numChoices == 3) {
      return selection;
    } else {
      return requestCardsPassed(hand);
    }
  } else {
    return requestCardsPassed(hand);
  }
}

void heartsArea::invalidMoveDialog() {
  wxMessageDialog dialog(NULL, "You played an invalid card. If possible, you "
                               "must match the suit of the card lead. Please "
                               "try again.",
                         "Invalid Move", wxICON_EXCLAMATION);
  dialog.ShowModal();
}

bool heartsArea::endOfRoundDialog(std::vector<int> playersRoundScores,
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

heartsArea::~heartsArea() {}

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
