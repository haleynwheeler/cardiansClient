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
  newUserPane = new newUser(this);
  pageSizer->Add(newUserPane, 1, wxGROW);
  newUserPane->Hide();

  // page 3
  mainPane = new mainMenu(this);
  pageSizer->Add(mainPane, 1, wxGROW);
  mainPane->Hide();

  // eightsGame = new CrazyEightsGame(this);
  // eightsGame->getGui()->Show(false);
  //  SetSizer(backgroundSizer);
  Centre();

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
    pageSizer->Show(2, true);

  } else if (buttonSwitch == "New User") {
    // // switch to new user screen from login
    pageSizer->Show(2, true);
    // pageSizer->Prepend(newUserPane, 1, wxGROW);
    // // backgroundSizer->Prepend(theBackgroundDrawable, 1, wxEXPAND);
    // newUserPane->Show();

  } else if (buttonSwitch == "Create New User") {
    // switch to main menu screen from new user
    pageSizer->Show(1, true);

  } else if (buttonSwitch == "Hearts Local") {
    eightsGame = new CrazyEightsGame(this);
    pageSizer->Prepend(eightsGame->getGui(), 1, wxGROW);

  } else if (buttonSwitch == "Hearts Online") {
    pageSizer->Show(1, true);

  } else if (buttonSwitch == "Eights Local") {
    heartsGame = new HeartsGame(this);
    pageSizer->Prepend(heartsGame->getGui(), 1, wxGROW);

  } else if (buttonSwitch == "Eights Online") {
    pageSizer->Show(1, true);

  } else {
    eightsGame->hideGame();
    std::cout << "MainScreen" << std::endl;
    pageSizer->Show(mainPane, true, true);
  }

  //  backgroundSizer->Layout();
  pageSizer->Layout();
  // backgroundSizer->Layout();
}
