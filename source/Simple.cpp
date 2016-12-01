#include "Simple.h"
#include "GameLogic/HeartsGame.hpp"
#include "button.h"

#include <wx/sizer.h>

Simple::Simple(const wxString &title, clientInfo *theClientScreen)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
              theClientScreen->getClientScreenSize()),
      NI(0, ioService, std::cout) {

  NI.connect("127.0.0.1", 12000);

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
  heartsLobby = new lobby(this, wxT("Hearts"));
  pageSizer->Add(heartsLobby);
  heartsLobby->Show(false);

  // page 5
  eightsLobby = new lobby(this, wxT("Crazy Eights"));
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

  pageSizer->ShowItems(false);

  // switching to main screen from login button
  if (buttonSwitch == "Login") {
    pageSizer->Show(2, true);

  } else if (buttonSwitch == "New User") {
    // // switch to new user screen from login
    pageSizer->Show(1, true);
    // pageSizer->Prepend(newUserPane, 1, wxGROW);
    // // backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    // newUserPane->Show();

  } else if (buttonSwitch == "Create New User") {
    // switch to main menu screen from new user
    pageSizer->Show(2, true);

  } else if (buttonSwitch == "Hearts Local") {
    heartsGame = new HeartsGame(this);
    pageSizer->Add(heartsGame->getGui(), 1, wxGROW);
    //  heartsGame->hideGame();
    heartsGame->startGame();

  } else if (buttonSwitch == "Hearts Online") {
    pageSizer->Show(3, true);

  } else if (buttonSwitch == "Eights Local") {
    eightsGame = new CrazyEightsGame(this);
    pageSizer->Prepend(eightsGame->getGui(), 1, wxGROW);

  } else if (buttonSwitch == "Eights Online") {
    pageSizer->Show(4, true);

  } else if (buttonSwitch == "Settings") {
    pageSizer->Show(2, true);
    wxMessageBox(wxT("Settings"));

  } else if (buttonSwitch == "Hearts Rules") {
    pageSizer->Show(2, true);
    wxMessageBox(wxT("Hearts rullleeesss"));

  } else if (buttonSwitch == "Eights Rules") {
    pageSizer->Show(2, true);
    wxMessageBox(
        wxT("Crazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssssCrazy Eights RUlesssssCrazy Eights RUlesssssCrazy Eights "
            "RUlesssss"));

  } else if (buttonSwitch == "Game Stats") {
    pageSizer->Show(2, true);
    wxMessageBox(wxT("Game Stats"));

  } else if (buttonSwitch == "Log Out") {
    pageSizer->Show(2, true);
    std::string msg = "Are you sure you want to log out?\n\n";
    wxMessageDialog dialog(NULL, msg, "Log Out", wxYES_NO);
    auto decision = dialog.ShowModal();
    if (decision == wxID_YES) {
      // pageSizer->Show(2, false);
      pageSizer->ShowItems(false);
      pageSizer->Show(loginPane, true);
    } else {
      pageSizer->Show(2, true);
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
