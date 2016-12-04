#include "playArea.h"
#include "button.h"
#include "imageInsert.h"
#include <iostream>

playArea::playArea(wxFrame *parent, clientInfo *client)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = client;
  setUpScreen(parent);
}

playArea::playArea(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL, wxPanelNameStr) {
  screenInfo = new clientInfo();
  setUpScreen(parent);
}

void playArea::updateCardBacks() {}

void playArea::setUpScreen(wxFrame *parent) {
  int cardWidth = 20;
  int cardHeight = 100;
  cardBackType = 14;
  Card *dummyCard = new Card(HEARTS, TWO);
  maxHandSize = 31;

  thePlayerHandSize = playerOneHandSize = playerTwoHandSize =
      playerThreeHandSize = 5;

  upperPortion = new wxBoxSizer(wxHORIZONTAL);
  middlePortion = new wxBoxSizer(wxHORIZONTAL);
  lowerPortion = new wxBoxSizer(wxHORIZONTAL);

  fieldArea = new wxBoxSizer(wxHORIZONTAL);
  verticalfieldArea = new wxBoxSizer(wxVERTICAL);
  discardPile = new wxBoxSizer(wxHORIZONTAL);

  yourHand = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerOneLabel = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerTwoLabel = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *playerThreeLabel = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *userLabel = new wxBoxSizer(wxHORIZONTAL);

  playerOne = new wxBoxSizer(wxVERTICAL);
  playerTwo = new wxBoxSizer(wxHORIZONTAL);
  playerThree = new wxBoxSizer(wxVERTICAL);
  theMainSizer = new wxBoxSizer(wxVERTICAL);
  fullSizer = new wxBoxSizer(wxHORIZONTAL);

  // COLLAPSIBLE PANE
  sidePane =
      new wxCollapsiblePane(this, wxID_ANY, "Menu", wxDefaultPosition,
                            screenInfo->sidePanelSize(), wxCP_NO_TLW_RESIZE);

  win = sidePane->GetPane();
  paneSz = new wxBoxSizer(wxVERTICAL);

  wxButton *settingsBtn = new wxButton(
      win, wxID_ANY, wxT("Eights Settings"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *eightsRulesBtn = new wxButton(
      win, wxID_ANY, wxT("Rules"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *statsBtn = new wxButton(
      win, wxID_ANY, wxT("Eights Stats"), wxDefaultPosition,
      screenInfo->sidePaneBtnSize(), 0, wxDefaultValidator, wxButtonNameStr);

  win->SetBackgroundColour(wxColour(0, 0, 0));
  sidePane->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  sidePane->SetForegroundColour(wxColour(255, 255, 255));

  settingsBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  settingsBtn->SetForegroundColour(wxColour(255, 255, 255));

  eightsRulesBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  eightsRulesBtn->SetForegroundColour(wxColour(255, 255, 255));

  statsBtn->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  statsBtn->SetForegroundColour(wxColour(255, 255, 255));

  paneSz->Add(settingsBtn);
  paneSz->Add(eightsRulesBtn);
  paneSz->Add(statsBtn);

  win->SetSizer(paneSz);
  paneSz->SetSizeHints(win);

  // END PANE

  topLogo = new wxBitmapButton(
      this, wxID_ANY, wxBitmap("../res/TextLogo.png", wxBITMAP_TYPE_PNG),
      wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  topLogo->SetBackgroundColour(wxColour(90, 5, 18, 0));

  SetFont(
      wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  playerOneInfo = new wxStaticText(this->GetParent(), wxID_ANY,
                                   "Drax the Destroyer", wxDefaultPosition,
                                   wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  playerTwoInfo = new wxStaticText(this->GetParent(), wxID_ANY, "Star-Lord",
                                   wxDefaultPosition, wxDefaultSize,
                                   wxALIGN_CENTRE_HORIZONTAL);

  playerThreeInfo =
      new wxStaticText(this->GetParent(), wxID_ANY, "Groot", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  userInfo =
      new wxStaticText(this->GetParent(), wxID_ANY, "You", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

  playerOneInfo->SetForegroundColour(wxColour(255, 255, 255));
  playerTwoInfo->SetForegroundColour(wxColour(255, 255, 255));
  playerThreeInfo->SetForegroundColour(wxColour(255, 255, 255));
  userInfo->SetForegroundColour(wxColour(255, 255, 255));

  playerOneLabel->Add(playerOneInfo);
  playerTwoLabel->Add(playerTwoInfo);
  playerThreeLabel->Add(playerThreeInfo);
  userLabel->Add(userInfo);

  Deck = new playerCard(this->GetParent(), cardBackType,
                        screenInfo->getLargeCardSize(), TRUE);
  Deck->setDrewCardFunction(humanDrewCard);
  Deck->Hide();

  for (int i = 0; i < 1; i++) {
    Discard[i] = new playerCard(
        parent, dummyCard, screenInfo->getLargeCardSize(), cardBackType, TRUE);
    discardPile->Add(Discard[i]);
  }
  discardPile->ShowItems(false);

  yourHand->Add(userLabel);
  playerCard *yourCard =
      new playerCard(this->GetParent(), dummyCard,
                     screenInfo->getLargeCardSize(), cardBackType, TRUE);
  handCards.push_back(yourCard);
  yourHand->Add(yourCard);
  for (int i = 0; i < maxHandSize; i++) {
    playerCard *card =
        new playerCard(this->GetParent(), dummyCard,
                       screenInfo->getSmallCardSize(), 14, FALSE);
    handCards.push_back(card);
    yourHand->Add(card);
    if (i >= thePlayerHandSize) {
      yourHand->Hide(i);
    }
  }
  yourHand->ShowItems(false);

  playerOne->Add(playerOneLabel);
  playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
                                    screenInfo->getLargeHorCardSize());
  playerOne->Add(card, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 2, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerOne->Add(card);
    if (i >= playerOneHandSize) {
      playerOne->Hide(i);
    }
  }
  playerOne->ShowItems(false);

  std::cout << "PlayerTwo Set Up" << std::endl;
  playerTwo->Add(playerTwoLabel);
  playerCard *card1 = new playerCard(this->GetParent(), 3, cardBackType,
                                     screenInfo->getLargeCardSize());
  playerTwo->Add(card1, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 3, cardBackType,
                                      screenInfo->getSmallCardSize(), false);
    playerTwo->Add(card);
    if (i >= playerTwoHandSize) {
      playerTwo->Hide(i);
    }
  }
  playerTwo->ShowItems(false);
  std::cout << "Player Two Done" << std::endl;

  playerThree->Add(playerThreeLabel);
  playerCard *card2 = new playerCard(this->GetParent(), 4, cardBackType,
                                     screenInfo->getLargeHorCardSize());
  playerThree->Add(card2, wxRESERVE_SPACE_EVEN_IF_HIDDEN);
  for (int i = 0; i < maxHandSize - 1; i++) {
    playerCard *card = new playerCard(this->GetParent(), 4, cardBackType,
                                      screenInfo->getSmallHorCardSize(), false);
    playerThree->Add(card);
    if (i >= playerThreeHandSize) {
      playerThree->Hide(i);
    }
  }
  playerThree->ShowItems(false);

  fieldArea->Add(Deck);
  fieldArea->Add(discardPile);

  verticalfieldArea->AddSpacer(screenInfo->c8middleVerSpace());
  verticalfieldArea->Add(fieldArea);
  verticalfieldArea->AddSpacer(screenInfo->c8middleVerSpace());

  upperPortion->Add(topLogo);
  upperPortion->AddSpacer(screenInfo->c8StrandardBorder()); //
  upperPortion->Add(playerTwoLabel);
  upperPortion->AddSpacer(10);
  upperPortion->Add(playerTwo, wxALIGN_CENTRE_VERTICAL);
  // upperPortion->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .3);
  // upperPortion->Add(playerThreeLabel);

  middlePortion->AddSpacer(screenInfo->c8StrandardBorder()); //
  middlePortion->Add(playerOneLabel);
  middlePortion->AddSpacer(10);

  middlePortion->Add(playerOne, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(screenInfo->c8MiddleHorSpace());
  middlePortion->Add(verticalfieldArea);
  middlePortion->AddSpacer(screenInfo->c8MiddleHorSpace());
  middlePortion->Add(playerThree, wxALIGN_BOTTOM);
  middlePortion->AddSpacer(10);

  middlePortion->Add(playerThreeLabel);

  lowerPortion->AddSpacer(screenInfo->c8LogoDifference()); //

  lowerPortion->Add(userLabel);
  lowerPortion->AddSpacer(10);

  lowerPortion->Add(yourHand);

  theMainSizer->AddSpacer(10); //
  theMainSizer->Add(upperPortion);
  theMainSizer->AddSpacer(20); //
  theMainSizer->Add(middlePortion);
  theMainSizer->Add(lowerPortion, wxBOTTOM);

  fullSizer->Add(theMainSizer);
  fullSizer->Add(sidePane);
  // SetSizerAndFit(theMainSizer);
  SetSizerAndFit(fullSizer);

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
  if (hand.size() > 0) {
    // yourHand->Add(userInfo);
    auto firstCard = hand.back();
    hand.pop_back();
    for (auto &&handCard : hand) {
      Card *temp = new Card(handCard.getSuit(), handCard.getValue());
      playerCard *card = new playerCard(
          this->GetParent(), temp, screenInfo->getSmallCardFront(), 14, false);
      card->setMoveFunction(humanMadeMove);
      handCards.push_back(card);
      yourHand->Add(card);
    }
    Card *temp = new Card(firstCard.getSuit(), firstCard.getValue());
    playerCard *card = new playerCard(this->GetParent(), temp,
                                      screenInfo->getCardFront(), 14, TRUE);
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
  middlePortion->Layout();
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
  middlePortion->Layout();
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
  std::vector<Card> tempDisc;
  tempDisc.push_back(topOfDiscardPile);
  updateFieldArea(false, tempDisc, true);
  this->Refresh();
  this->Update();
  Thaw();
}

void playArea::updateOnlinePlayArea(std::vector<Card> hand,
                                    std::vector<int> handSizes,
                                    std::vector<Card> field) {
  Freeze();
  playerZero(hand);
  for (int i = 0; i < 4; i++) {
    playerAi(i, handSizes.at(i));
  }
  updateFieldArea(FALSE, field, FALSE);
  Refresh();
  Update();
  Thaw();
}

void playArea::updatePlayArea(int playerId, std::vector<Card> hand,
                              bool deckEmpty, Card topOfDiscardPile) {
  // Freeze();
  if (playerId == 0) {
    std::cout << "your turn" << std::endl;
    std::vector<int> aiHandSize;
    aiHandSize.clear();
    for (int i = 1; i < 5; i++) {
      aiHandSize.push_back(std::rand() % 13);
    }
    std::vector<Card> disc;
    disc.push_back(topOfDiscardPile);
    updateOnlinePlayArea(hand, aiHandSize, disc);
  }

  // wxMessageDialog dialog(this, wxID_ANY, ".lol", wxPoint(0, 0),
  // wxDefaultSize, wxDEFAULT_DIALOG_STYLE, wxDialogNameSt);
  // auto decision = dialog.ShowModal();
  // dialog.Desrtoy();
  // Thaw();
  // ProcessPendingEvents();
}

void playArea::updateFieldArea(bool deckEmpty, std::vector<Card> field,
                               bool initialize) {

  Deck->updateDeck(deckEmpty, screenInfo->getcardBackType());
  Deck->setDrewCardFunction(humanDrewCard);
  for (int i = 0; i < 1; i++) {
    if (field.size() != 0) {
      Discard[i]->updateCard(field.back(), TRUE);
      field.pop_back();
    } else {
      Discard[i]->Hide();
    }
  }
  fieldArea->Show(true);
  // fieldArea->Add(Deck);
  // fieldArea->Add(Discard);
  // fieldArea->Layout();
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

void playArea::hideGame() { fullSizer->Show(false); }

playArea::~playArea() {}

// https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/Galaxy-2048x1152.jpg/512px-Galaxy-2048x1152.jpg
