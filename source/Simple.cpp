#include "Simple.h"
#include "button.h"

#include <wx/sizer.h>

Simple::Simple(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition,
              wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
                     wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7)) {
  // SetMaxSize(
  // wxSize(wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
  // wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7)));
  // SetMinSize(
  // wxSize(wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5,
  // wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .7)));

  backgroundSizer = new wxBoxSizer(wxHORIZONTAL);
  baseBackground *theBackgroundDrawable = new baseBackground(
      this, wxT("../res/background.jpg"), wxBITMAP_TYPE_JPEG);
  backgroundSizer->Add(theBackgroundDrawable, 1, wxEXPAND);

  pageSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(pageSizer);

  // page 1
  loginPane = new login(this);
  pageSizer->Add(loginPane, 1, wxGROW);

  // page 2
  mainPane = new mainMenu(this);
  mainPane->Hide();

  // page 3
  newUserPane = new newUser(this);
  newUserPane->Hide();

  eightsGame = new CrazyEightsGame(this);
  eightsGame->Hide();
  //  SetSizer(backgroundSizer);
  Centre();

  Bind(wxEVT_BUTTON,
       [=](wxCommandEvent &event) {
         std::cout << "Caught Button" << std::endl;
         buttonText = (wxButton *)event.GetEventObject();
         wxString buttonSwitch = buttonText->GetLabel();
         // std::cout << "this is button text " << buttonSwitch << std::endl;
         switchPage(buttonSwitch);
       },
       wxID_ANY);
}

void Simple::switchPage(wxString buttonSwitch) {

  pageSizer->Detach(0);
  // switch (pageno) {
  // case 1:
  //   loginPane->Hide();
  //   pageSizer->Prepend(mainPane, 1, wxGROW);
  //   mainPane->Show();
  //   break;
  // case 2:
  //   mainPane->Hide();
  //   pageSizer->Prepend(loginPane, 1, wxGROW);
  //   loginPane->Show();
  //   break;
  // }

  // switching to main screen from login button
  if (buttonSwitch == "Login") {
    //  std::cout << "HERERERERE";
    loginPane->Hide();
    newUserPane->Hide();
    // eightsGame->Hide();
    pageSizer->Prepend(mainPane, 1, wxGROW);
    // backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    mainPane->Show();
  } else if (buttonSwitch == "New User") {
    // switch to new user screen from login
    loginPane->Hide();
    mainPane->Hide();
    // eightsGame->Hide();
    pageSizer->Prepend(newUserPane, 1, wxGROW);
    // backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    newUserPane->Show();
  } else if (buttonSwitch == "Create New User") {
    // switch to main menu screen from new user
    loginPane->Hide();
    newUserPane->Hide();
    // eightsGame->Hide();
    pageSizer->Prepend(mainPane, 1, wxGROW);
    //  backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    mainPane->Show();
  } else if (buttonSwitch == "Hearts Local") {
    loginPane->Hide();
    mainPane->Hide();
    //  eightsGame->Hide();
    pageSizer->Prepend(newUserPane, 1, wxGROW);
    newUserPane->Show();
  } else if (buttonSwitch == "Hearts Online") {
    loginPane->Hide();
    mainPane->Hide();
    //  eightsGame->Hide();
    pageSizer->Prepend(newUserPane, 1, wxGROW);
    newUserPane->Show();
  } else if (buttonSwitch == "Eights Local") {
    loginPane->Hide();
    mainPane->Hide();
    newUserPane->Hide();
    //  pageSizer->Prepend(eightsGame, 1, wxGROW);
    //  eightsGame->startNewRound();
  } else if (buttonSwitch == "Eights Online") {
    loginPane->Hide();
    mainPane->Hide();
    //  eightsGame->Hide();
    pageSizer->Prepend(newUserPane, 1, wxGROW);
    newUserPane->Show();
  } else {
    std::cout << "Nothing caught" << std::endl;
  }

  //  backgroundSizer->Layout();
  pageSizer->Layout();
  // backgroundSizer->Layout();
}
