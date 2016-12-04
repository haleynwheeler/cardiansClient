#include "Simple.h"
#include "GameLogic/HeartsGame.hpp"
#include "button.h"

#include <wx/sizer.h>

Simple::Simple(const wxString &title, clientInfo *theClientScreen)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
              theClientScreen->getClientScreenSize()),
      NI(0, ioService, std::cout) {

  NI.connect("127.0.0.1", 12000);
  isConnected = NI.isConnected();
  if (!isConnected) {
    wxMessageDialog dialog(NULL, "Unable to connect to the server. Please "
                                 "choose to play in offline mode.");
    dialog.ShowModal();
  }
  screenInfo = theClientScreen;

  pageSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(pageSizer);

  // page 1
  loginPane = new login(this);
  pageSizer->Add(loginPane, 1, wxGROW);

  // page 2
  newUserPane = new newUser(this);
  pageSizer->Add(newUserPane, 1, wxGROW);
  newUserPane->Hide();

  // page 3
  mainPane = new mainMenu(this);
  pageSizer->Add(mainPane, 1, wxGROW);
  mainPane->Hide();

  // page 4
  heartsLobby = new lobby(this, wxT("HEARTS"));
  pageSizer->Add(heartsLobby);
  heartsLobby->Show(false);

  // page 5
  eightsLobby = new lobby(this, wxT("EIGHTS"));
  pageSizer->Add(eightsLobby);
  eightsLobby->Hide();

  eightsGame = nullptr;
  heartsGame = nullptr;
  // //  SetSizer(backgroundSizer);
  Centre();
  SetBackgroundColour(wxColour(0, 0, 0));
  Bind(wxEVT_BUTTON,
       [=](wxCommandEvent &event) {
         buttonText = (wxButton *)event.GetEventObject();
         wxString buttonSwitch = buttonText->GetLabel();
         std::cout << buttonSwitch << std::endl;
         switchPage(buttonSwitch);
       },
       wxID_ANY);
}

void Simple::switchPage(wxString buttonSwitch) {

  if (buttonSwitch != "Eights Settings" || buttonSwitch != "Rules" ||
      buttonSwitch != "Eights Stats") {

    pageSizer->ShowItems(false);
  }

  // switching to main screen from login button
  if (buttonSwitch == "Login") {
    pageSizer->Show(mainPane, true);

  } else if (buttonSwitch == "Eights Settings") {
    // pageSizer->Show(mainPane, true);
    wxMessageBox(wxT("Settings"));

    // pageSizer->Prepend(eightsGame->getGui(), 1, wxGROW);

  } else if (buttonSwitch == "Rules") {
    // pageSizer->Show(mainPane, true);
    wxMessageBox(wxT("Rules"));

  } else if (buttonSwitch == "Eights Stats") {
    // pageSizer->Show(mainPane, true);
    wxMessageBox(wxT("stats"));

  } else if (buttonSwitch == "New User") {
    // // switch to new user screen from login
    pageSizer->Show(newUserPane, true);
    // pageSizer->Prepend(newUserPane, 1, wxGROW);
    // // backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    // newUserPane->Show();

  } else if (buttonSwitch == "Offline Only") {
    // // switch to main screen  from login. Don't connect to server
    pageSizer->Show(mainPane, true);
    isConnected = false;

  } else if (buttonSwitch == "Create New User") {
    // switch to main menu screen from new user
    pageSizer->Show(loginPane, true);

  } else if (buttonSwitch == "Back To Login") {
    // switch to main menu screen from new user
    pageSizer->Show(loginPane, true);

  } else if (buttonSwitch == "Hearts Local") {
    heartsGame = new HeartsGame(this, screenInfo);
    pageSizer->Add(heartsGame->getGui(), 1, wxGROW);
    //  heartsGame->hideGame();
    heartsGame->startGame();

  } else if (buttonSwitch == "Hearts Online") {
    if (isConnected) {
      pageSizer->Show(3, true);
      heartsLobby->requestGames();
    } else {
      pageSizer->Show(mainPane, true);
      wxMessageBox(wxT("This functionality is not available in offline mode."));
    }

  } else if (buttonSwitch == "Eights Local") {
    eightsGame = new CrazyEightsGame(this, screenInfo);
    pageSizer->Prepend(eightsGame->getGui(), 1, wxGROW);

  } else if (buttonSwitch == "Eights Online") {
    if (isConnected) {
      pageSizer->Show(4, true);
      eightsLobby->requestGames();
    } else {
      pageSizer->Show(mainPane, true);
      wxMessageBox(wxT("This functionality is not available in offline mode."));
    }

  } else if (buttonSwitch == "Cardbacks") {
    pageSizer->Show(mainPane, true);
    screenInfo->changeBackgroundDialog();

  } else if (buttonSwitch == "Hearts Rules") {
    pageSizer->Show(mainPane, true);
    wxMessageBox(wxT(
        "Object of the game: To be the player with the fewest "
        "points at the end of the game.\n\n At the beginning of "
        "the  game, a pass is made of three cards.\n\n To start, the player "
        "holding the two of "
        "clubs leads the round.\n\n Each player must follow  suit if "
        "possible. If a player does not a have of suit to play, they may "
        "either discard of another suit or break hearts.\n\n The highest "
        "card played of the suit led takes the trick, and the winner of "
        "that trick leads the next round.\n\n At the end of the round, each "
        "heart still held by a player is worth 1 point, and the queen of "
        "spades is worth 13 points."));

  } else if (buttonSwitch == "Eights Rules") {
    pageSizer->Show(mainPane, true);
    wxMessageBox(wxT(
        "Object of game: Get rid of cards in your hand onto a "
        "discard pile by matching number or suit of previous discarded "
        "card.\n\n Each player in turn must either play a legal card face up on"
        "top of discard pile or draw from the undealt stock.\n\n If the top of "
        "the"
        "discard pile is not an eight, you may play a card that matches the"
        "previous suit or rank.\n\n An eight may be played on any card, and the"
        "player of the eight must nominate a suit.\n\n If an eight is on the "
        "top"
        "of"
        "the pile, you must play either an eight or a card of the suit"
        "nominated.\n\n The first player who gets rid of their hand is the "
        "winner,"
        "and the other players score penalty points for the cards left in their"
        "hand.\n\n Penalty points are as follows: -50 for an eight, 10 for a"
        "picture, and spot cards at face value."));

  } else if (buttonSwitch == "Game Stats") {
    pageSizer->Show(mainPane, true);
    wxMessageBox(wxT("Game Stats"));

  } else if (buttonSwitch == "Log Out") {
    pageSizer->Show(mainPane, true);
    std::string msg = "Are you sure you want to log out?\n\n";
    wxMessageDialog dialog(NULL, msg, "Log Out", wxYES_NO);
    auto decision = dialog.ShowModal();
    if (decision == wxID_YES) {
      // pageSizer->Show(2, false);
      pageSizer->ShowItems(false);
      pageSizer->Show(loginPane, true);
    } else {
      pageSizer->Show(mainPane, true);
    }
  } else {
    if (heartsGame) {
      heartsGame->hideGame();
    }
    if (eightsGame) {
      eightsGame->hideGame();
    }

    std::cout << "MainScreen" << std::endl;
    pageSizer->Show(mainPane, true, true);
  }

  //  backgroundSizer->Layout();
  pageSizer->Layout();
  // backgroundSizer->Layout();
}

void Simple::sendServerMsg(std::string msg) { NI.send(msg); }

// void Simple::setServerReceivedMsgFunc(std::function<void(std::string)> func)
// {
//   auto msg = NI.recieve();
//   func(); }

std::string Simple::getResponse() { return NI.recieve(); }
