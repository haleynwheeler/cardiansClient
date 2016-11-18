#include "newUser.h"
#include "button.h"
#include "imageInsert.h"

// This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
// It also has the main logo.

newUser::newUser(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5,
                     wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5),
              wxTAB_TRAVERSAL, wxPanelNameStr) {

  imageInsert *theLogo = new imageInsert(this, wxT("../res/logo.png"),
                                         wxBITMAP_TYPE_PNG, 300, 600);

  // wxBoxSizer *verticalOne = new wxBoxSizer(wxVERTICAL);
  // wxBoxSizer *verticalTwo = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalContainerTwo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);

  usernameText = new wxTextCtrl(this, 0, "Username", wxDefaultPosition);
  passwordText = new wxTextCtrl(this, 0, "Password", wxDefaultPosition);

  // horizontalContainer->Add(new
  // wxTextCtrl(this,0,"Password",wxDefaultPosition,
  // wxSize(140,60)),1,wxCENTER,0);
  wxButton *user = new wxButton(this, newUserButton, wxT("Create New User"),
                                wxDefaultPosition, wxSize(280, 100), 0,
                                wxDefaultValidator, wxButtonNameStr);
  // verticalTwo->Add(user);
  horizontalContainer->Add(usernameText);
  horizontalContainer->Add(passwordText);

  horizontalContainerTwo->Add(user);

  user->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  user->SetForegroundColour(wxColour(wxT("WHITE")));

  // horizontalContainer->Add(verticalOne);
  // horizontalContainer->Add(verticalTwo);

  theSizer->Add(theLogo);
  theSizer->Add(horizontalContainer);
  theSizer->Add(horizontalContainerTwo);
  // theSizer->Add(verticalOne, wxLEFT, 0);
  // theSizer->Add(verticalTwo, wxRIGHT, 0);

  SetSizerAndFit(theSizer);
  Center();

  // wxDECLARE_EVENT_TABLE();
}

void newUser::OnNewUser(wxCommandEvent &event) { event.Skip(); }

newUser::~newUser() {}

wxBEGIN_EVENT_TABLE(newUser, wxPanel)
    // EVT_BUTTON(loginButton, newUser::OnLogin)
    EVT_BUTTON(newUserButton, newUser::OnNewUser) wxEND_EVENT_TABLE()
