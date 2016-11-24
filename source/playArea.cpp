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
  cardBackType = 14;
  Card *dummyCard = new Card(HEARTS, TWO);
  maxHandSize = 31;

  int heightLeft = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7;
  heightLeft -= 850;

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 5;

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  verticalfieldArea = new wxBoxSizer(wxVERTICAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);
  theMainSizer = new wxBoxSizer(wxVERTICAL);

  wxBitmapButton *topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  Deck = new playerCard(this->GetParent(), cardBackType, wxSize(100, 70), TRUE);
  Deck->setDrewCardFunction(humanDrewCard);
  Deck->Hide();

  Discard = new playerCard(parent, dummyCard, wxSize(80, 120), cardBackType);
  Discard->Hide();

  for (int i = 0; i < maxHandSize; i++) {
    playerCard *card =
        new playerCard(this->GetParent(), dummyCard, wxSize(80, 120), 14);
    handCards.push_back(card);
    yourHand->Add(card);
    if (i >= thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }
  yourHand->ShowItems(false);

  playerCard *card =
      new playerCard(this->GetParent(), 2, cardBackType, wxSize(100, 70));
  playerOne->Add(card);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
                                      wxSize(100, 20), false);
    playerOne->Add(card);
    if (i >= playerOneHandSize) {
      playerOne->Hide(i);
    }
  }
  playerOne->ShowItems(false);

  playerCard *card1 =
      new playerCard(this->GetParent(), 3, cardBackType, wxSize(70, 100));
  playerTwo->Add(card1);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 3, cardBackType,
                                      wxSize(20, 100), false);
    playerTwo->Add(card);
    if (i >= playerTwoHandSize) {
      playerTwo->Hide(i);
    }
  }
  playerTwo->ShowItems(false);

  playerCard *card2 =
      new playerCard(this->GetParent(), 4, cardBackType, wxSize(100, 70));
  playerThree->Add(card2);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 4, cardBackType,
                                      wxSize(100, 20), false);
    playerThree->Add(card);
    if (i >= playerThreeHandSize) {
      playerThree->Hide(i);
    }
  }
  playerThree->ShowItems(false);

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
  middlePortion->Add(playerOne, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(270);
  middlePortion->Add(verticalfieldArea);
  middlePortion->AddSpacer(270);
  middlePortion->Add(playerThree, wxALIGN_BOTTOM);

  lowerPortion->AddSpacer(100);
  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10);
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20);
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);
  SetSizerAndFit(theMainSizer);
  Hide();
}

void playArea::setDrewCardFunction(std::function<void()> f) {
  humanDrewCard = f;
}

void playArea::setMadeMoveFunction(std::function<void(Card)> f) {
  humanMadeMove = f;
}

void playArea::playerZero(std::vector<Card> hand) {
  yourHand->Clear(true);
  handCards.clear();
  std::cout << "My hand: " << std::endl;
  for (auto &&handCard : hand) {
    std::cout << handCard.getValue() << " of " << handCard.getSuit()
              << std::endl;
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

void playArea::playerAi(int playerId, int handSize) {
  std::cout << "Player " << playerId << " has " << handSize << " cards."
            << std::endl;
  switch (playerId) {
  case 1:
    updatePlayerOne(handSize);
    break;

  case 2:
    updatePlayerTwo(handSize);
    break;

  case 3:
    updatePlayerThree(handSize);
    break;
  }
  theMainSizer->Layout();
}

void playArea::updatePlayerOne(int handSize) {
  playerOne->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      // std::cout << "Hiding card number " << i << std::endl;
      playerOne->Hide(i);
    }
  }
  playerOne->Layout();
  // middlePortion->Layout();
}

void playArea::updatePlayerTwo(int handSize) {
  playerTwo->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      playerTwo->Hide(i);
    }
  }
  playerTwo->Layout();
}

void playArea::updatePlayerThree(int handSize) {
  playerThree->ShowItems(true);
  for (int i = 0; i < maxHandSize; i++) {
    if (i >= handSize) {
      playerThree->Hide(i);
    }
  }
  playerThree->Layout();
}

void playArea::initializePlayArea(std::vector<Card> humanHand,
                                  Card topOfDiscardPile) {
  std::cout << "Creating area" << std::endl;
  Show();
  Freeze();
  playerZero(humanHand);
  for (int i = 1; i < 4; i++) {
    playerAi(i, humanHand.size());
  }
  updateFieldArea(false, topOfDiscardPile, true);
  this->Refresh();
  this->Update();
  Thaw();
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {
  Freeze();
  switch (playerId) {
  case 0:
    playerZero(hand);
    break;
  case 1:
  case 2:
  case 3:
    playerAi(playerId, hand.size());
    std::cout << "Computer Played" << std::endl;
    break;
  }
  updateFieldArea(deckEmpty, topOfDiscardPile, false);
  this->Refresh();
  this->Update();
  Thaw();
}

void playArea::updateFieldArea(bool deckEmpty, Card topOfDiscardPile,
                               bool initialize) {
  if (initialize) {
    fieldArea->Clear(true);
  } else {
    fieldArea->Clear();
  }

  if (!deckEmpty) {
    Deck =
        new playerCard(this->GetParent(), cardBackType, wxSize(80, 120), false);
  } else {
    Deck =
        new playerCard(this->GetParent(), cardBackType, wxSize(80, 120), true);
  }
  Deck->setDrewCardFunction(humanDrewCard);

  Card *tempest =
      new Card(topOfDiscardPile.getSuit(), topOfDiscardPile.getValue());
  Discard = new playerCard(this->GetParent(), tempest, wxSize(80, 120), 14);
  fieldArea->Add(Deck);
  fieldArea->Add(Discard);
  fieldArea->Layout();
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
  auto yes = dialog.ShowModal();
  if (yes == wxID_OK) {
    int choice = dialog.GetSelection();
    return static_cast<Suit>(choice);
  } else {
    return UNDEFINED;
  }
}

void playArea::aiPickedSuitDialog(Suit suitSpecified) {
  std::string msg = "The computer played an eight and has chosen the suit ";
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

bool playArea::endOfGameDialog(std::vector<int> playersRoundScores,
                               std::vector<int> playersOverallScores) {
  std::string msg = "The Game is over! Here are the final scores:\n \n";
  msg += "SCORES:\n";
  msg += "YOU:\t";
  msg += "Round Score: " + std::to_string(playersRoundScores[0]) + "\n";
  msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[0]);

  for (int i = 1; i < 4; i++) {
    msg += "\nAI " + std::to_string(i) + ":\t";
    msg += "Round Score: " + std::to_string(playersRoundScores[i]) + "\n";
    msg += "\t\tOverall Score: " + std::to_string(playersOverallScores[i]);
  }

  msg += "\n\nWould you like to play again?";

  wxMessageDialog dialog(NULL, msg, "Game Over", wxYES_NO);
  auto decision = dialog.ShowModal();
  if (decision == wxID_YES) {
    return true;
  } else {
    return false;
  }
}

playArea::~playArea() {}

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
