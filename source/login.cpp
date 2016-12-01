#include "login.h"
#include "Simple.h"
#include "button.h"
#include "imageInsert.h"
#include "playArea.h"

#include <boost/algorithm/string.hpp>

// This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
// It also has the main logo.

login::login(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5,
                     wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5),
              wxTAB_TRAVERSAL, wxPanelNameStr) {

  imageInsert *theLogo = new imageInsert(this, wxT("../res/logo.png"),
                                         wxBITMAP_TYPE_PNG, 300, 600);

  wxBoxSizer *verticalOne = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *verticalTwo = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);

  usernameText = new wxTextCtrl(this, 0, "Username", wxDefaultPosition);
  wxButton *login =
      new wxButton(this, loginButton, wxT("Login"), wxDefaultPosition,
                   wxSize(200, 100), 0, wxDefaultValidator, wxButtonNameStr);
  // Button *login = new Button(wxT("Login"),parent, wxSize(100,100));
  verticalOne->Add(usernameText);
  verticalOne->Add(login);

  login->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  login->SetForegroundColour(wxColour(wxT("WHITE")));

  passwordText = new wxTextCtrl(this, 0, "Password", wxDefaultPosition);
  passwordText->SetDefaultStyle(wxTextAttr(wxTE_PASSWORD));

  wxButton *user =
      new wxButton(this, newUserButton, wxT("New User"), wxDefaultPosition,
                   wxSize(200, 100), 0, wxDefaultValidator, wxButtonNameStr);

  verticalTwo->Add(passwordText);
  verticalTwo->Add(user);

  user->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  user->SetForegroundColour(wxColour(wxT("WHITE")));

  horizontalContainer->Add(verticalOne);
  horizontalContainer->Add(verticalTwo);

  theSizer->Add(theLogo);
  theSizer->Add(horizontalContainer);

  SetSizerAndFit(theSizer);
  Center();
}

void login::OnNewUser(wxCommandEvent &event) { event.Skip(); }

void login::OnLogin(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  mainFrame->sendServerMsg(std::string("LOGIN"));
  auto msg = mainFrame->getResponse();
  receivedLoginFromServer(msg, event);
}

void login::receivedLoginFromServer(std::string msg, wxCommandEvent &event) {
  std::cout << msg << std::endl;
  if (boost::algorithm::starts_with(msg, "SUCCESS")) {
    std::cout << "Successful Login" << std::endl;
    event.Skip();
  } else if (boost::algorithm::starts_with(msg, "PASSWORD INCORRECT")) {
    std::cout << "Incorrect Password" << std::endl;
    // Prompt again with dialog box?
  } else if (boost::algorithm::starts_with(msg, "USER NOT FOUND")) {
    std::cout << "User Not Found" << std::endl;
    // Prompt to create a new user?
  } else {
    std::cout << "Unknown Message" << std::endl;
  }
}

login::~login() {}

wxBEGIN_EVENT_TABLE(login, wxPanel) EVT_BUTTON(loginButton, login::OnLogin)
    EVT_BUTTON(newUserButton, login::OnNewUser) wxEND_EVENT_TABLE()
