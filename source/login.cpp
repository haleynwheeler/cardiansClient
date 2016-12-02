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

  clientInfo *screenInfo = new clientInfo();

  imageInsert *theLogo =
      new imageInsert(this, wxT("../res/logo.png"), wxBITMAP_TYPE_PNG,
                      screenInfo->getClientScreenSize().GetWidth() * .25,
                      screenInfo->getClientScreenSize().GetHeight() * .7);

  wxBoxSizer *verticalOne = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *verticalTwo = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *logoHolder = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *labelHolder = new wxBoxSizer(wxHORIZONTAL);    // username label
  wxBoxSizer *labelHolderTwo = new wxBoxSizer(wxHORIZONTAL); // password label
  wxBoxSizer *offlineHolder = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *usernameLabel =
      new wxStaticText(this, wxID_ANY, "Username:", wxDefaultPosition);

  wxStaticText *passwordLabel =
      new wxStaticText(this, wxID_ANY, "Password:", wxDefaultPosition);

  usernameLabel->SetForegroundColour(wxColour(wxT("WHITE")));

  passwordLabel->SetForegroundColour(wxColour(wxT("WHITE")));

  usernameText = new wxTextCtrl(this, 0, "Username", wxDefaultPosition,
                                screenInfo->loginTextSize());
  wxButton *login = new wxButton(this, loginButton, wxT("Login"),
                                 wxDefaultPosition, screenInfo->loginBtnSize(),
                                 0, wxDefaultValidator, wxButtonNameStr);

  wxButton *loginOffline =
      new wxButton(this, wxID_ANY, wxT("Offline Only"), wxDefaultPosition,
                   screenInfo->loginOfflineBtnSize(), 0, wxDefaultValidator,
                   wxButtonNameStr);

  loginOffline->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  loginOffline->SetForegroundColour(wxColour(wxT("WHITE")));
  // Button *login = new Button(wxT("Login"),parent, wxSize(100,100));

  offlineHolder->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .145);
  offlineHolder->Add(loginOffline);

  labelHolder->Add(usernameLabel, 0, wxEXPAND, 0);
  verticalOne->Add(labelHolder);
  verticalOne->Add(usernameText);
  verticalOne->Add(login);

  login->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  login->SetForegroundColour(wxColour(wxT("WHITE")));

  passwordText = new wxTextCtrl(this, 0, "", wxDefaultPosition,
                                screenInfo->loginTextSize(), wxTE_PASSWORD,
                                wxDefaultValidator, wxButtonNameStr);
  // passwordText = new wxTextCtrl(this, 0, "Password", wxDefaultPosition);
  // passwordText->SetStyle(0, 100, wxTextAttr(wxTE_PASSWORD));

  wxButton *user = new wxButton(this, newUserButton, wxT("New User"),
                                wxDefaultPosition, screenInfo->loginBtnSize(),
                                0, wxDefaultValidator, wxButtonNameStr);
  labelHolderTwo->Add(passwordLabel);
  verticalTwo->Add(labelHolderTwo);
  verticalTwo->Add(passwordText);
  verticalTwo->Add(user);

  user->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  user->SetForegroundColour(wxColour(wxT("WHITE")));

  horizontalContainer->AddSpacer(screenInfo->getClientScreenSize().GetWidth() *
                                 .145);
  horizontalContainer->Add(verticalOne);
  // horizontalContainer->AddSpacer(screenInfo->getClientScreenSize().GetWidth()
  // *
  //.5);
  horizontalContainer->Add(verticalTwo);
  // horizontalContainer->Add(offlineHolder);

  // theSizer->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .5);
  logoHolder->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .3);
  logoHolder->Add(theLogo);
  theSizer->Add(logoHolder);
  theSizer->Add(labelHolder);
  theSizer->Add(horizontalContainer);
  theSizer->AddSpacer(10);
  theSizer->Add(offlineHolder);

  SetSizerAndFit(theSizer);
  Center();
}

void login::OnNewUser(wxCommandEvent &event) { event.Skip(); }

void login::OnLogin(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  std::string userName = usernameText->GetLineText(0).ToStdString();
  std::string password = passwordText->GetLineText(0).ToStdString();
  std::string sendMsg = "LOGIN " + userName + " " + password;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedLoginFromServer(receivedMsg, event);
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
