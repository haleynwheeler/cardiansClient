#include "newUser.h"
#include "Simple.h"
#include "button.h"
#include "clientInfo.h"
#include "imageInsert.h"
#include <boost/algorithm/string.hpp>

// This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
// It also has the main logo.

newUser::newUser(wxFrame *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
              wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) * .5,
                     wxSystemSettings::GetMetric(wxSYS_SCREEN_X) * .5),
              wxTAB_TRAVERSAL, wxPanelNameStr) {

  clientInfo *screenInfo = new clientInfo();

  imageInsert *theLogo =
      new imageInsert(this, wxT("../res/logo.png"), wxBITMAP_TYPE_PNG,
                      screenInfo->getClientScreenSize().GetWidth() * .25,
                      screenInfo->getClientScreenSize().GetHeight() * .7);

  // wxBoxSizer *verticalOne = new wxBoxSizer(wxVERTICAL);
  // wxBoxSizer *verticalTwo = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalContainerTwo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *logoHolder = new wxBoxSizer(wxHORIZONTAL);

  usernameText = new wxTextCtrl(this, 0, "Username", wxDefaultPosition,
                                screenInfo->newUserTextSize());
  passwordText = new wxTextCtrl(this, 0, "Password", wxDefaultPosition,
                                screenInfo->newUserTextSize());

  // horizontalContainer->Add(new
  // wxTextCtrl(this,0,"Password",wxDefaultPosition,
  // wxSize(140,60)),1,wxCENTER,0);
  wxButton *user = new wxButton(this, newUserButton, wxT("Create New User"),
                                wxDefaultPosition, screenInfo->newUserBtnSize(),
                                0, wxDefaultValidator, wxButtonNameStr);
  // verticalTwo->Add(user);
  horizontalContainer->AddSpacer(screenInfo->getClientScreenSize().GetWidth() *
                                 .25);
  horizontalContainer->Add(usernameText);
  horizontalContainer->Add(passwordText);

  horizontalContainerTwo->AddSpacer(
      screenInfo->getClientScreenSize().GetWidth() * .25);
  horizontalContainerTwo->Add(user);

  user->SetBackgroundColour(wxColour(90, 5, 18, wxALPHA_OPAQUE));
  user->SetForegroundColour(wxColour(wxT("WHITE")));

  // horizontalContainer->Add(verticalOne);
  // horizontalContainer->Add(verticalTwo);
  logoHolder->AddSpacer(screenInfo->getClientScreenSize().GetWidth() * .3);
  logoHolder->Add(theLogo);

  theSizer->Add(logoHolder);
  theSizer->Add(horizontalContainer);
  theSizer->Add(horizontalContainerTwo);
  // theSizer->Add(verticalOne, wxLEFT, 0);
  // theSizer->Add(verticalTwo, wxRIGHT, 0);

  SetSizerAndFit(theSizer);
  Center();

  // wxDECLARE_EVENT_TABLE();
}

void newUser::OnNewUser(wxCommandEvent &event) {
  Simple *mainFrame = (Simple *)GetParent();
  std::string userName = usernameText->GetLineText(0).ToStdString();
  std::string password = passwordText->GetLineText(0).ToStdString();
  std::string sendMsg = "REGISTER " + userName + " " + password;
  mainFrame->sendServerMsg(sendMsg);
  auto receivedMsg = mainFrame->getResponse();
  receivedNewUserFromServer(receivedMsg, event);
}

void newUser::receivedNewUserFromServer(std::string msg,
                                        wxCommandEvent &event) {
  if (boost::algorithm::starts_with(msg, "SUCCESS")) {
    std::cout << "Created new user successfully" << std::endl;
    event.Skip();
  } else if (boost::algorithm::starts_with(msg, "USERNAME TAKEN")) {
    std::cout << "Please pick a different username. This one already exists"
              << std::endl;
  } else {
    std::cout << "Unknown Message" << std::endl;
  }
}

newUser::~newUser() {}

wxBEGIN_EVENT_TABLE(newUser, wxPanel)
    // EVT_BUTTON(loginButton, newUser::OnLogin)
    EVT_BUTTON(newUserButton, newUser::OnNewUser) wxEND_EVENT_TABLE()
