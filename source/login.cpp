#include "login.h"
#include "button.h"
#include "playArea.h"
#include "imageInsert.h"


//This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
//It also has the main logo.

login::login(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {

  imageInsert *theLogo = new imageInsert(this, wxT("logo.png"), wxBITMAP_TYPE_PNG,
      300,600);

  wxBoxSizer *verticalOne = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *verticalTwo = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalContainer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *theSizer = new wxBoxSizer(wxVERTICAL);

  usernameText = new wxTextCtrl(this,0,"Username",wxDefaultPosition);
   wxButton *login = new wxButton(this, loginButton, wxT("Login"), wxDefaultPosition,
   wxSize(200,100), 0, wxDefaultValidator, wxButtonNameStr);
    //Button *login = new Button(wxT("Login"),parent, wxSize(100,100));
  verticalOne->Add(usernameText);
  verticalOne->Add(login);

  login->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
  login->SetForegroundColour(wxColour(wxT("WHITE")));


  passwordText = new wxTextCtrl(this,0,"Password",wxDefaultPosition);
  wxButton *user = new wxButton(this, newUserButton, wxT("Create New User"), wxDefaultPosition,
      wxSize(200,100), 0, wxDefaultValidator, wxButtonNameStr);
  verticalTwo->Add(passwordText);
   verticalTwo->Add(user);

   user->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
   user->SetForegroundColour(wxColour(wxT("WHITE")));

  horizontalContainer->Add(verticalOne);
  horizontalContainer->Add(verticalTwo);

  theSizer->Add(theLogo);
  theSizer->Add(horizontalContainer);
  //theSizer->Add(verticalOne, wxLEFT, 0);
  //theSizer->Add(verticalTwo, wxRIGHT, 0);

  SetSizerAndFit(theSizer);
  Center();

  //wxDECLARE_EVENT_TABLE();
}

void login::OnNewUser(wxCommandEvent & event)
{
   wxString usernameVal = usernameText->GetValue();
   wxString passwordVal = passwordText->GetValue();
   wxString userPass = "New User Button Pressed. \nUsername: " + usernameVal + "\n Password: " + passwordVal;
   wxMessageBox(userPass);
  // wxMessageDialog dialog(NULL, "new user click", "wxButton Click");
  // dialog.ShowModal();

}
void login::OnLogin(wxCommandEvent & event)
{
  wxString usernameVal = usernameText->GetValue();
  wxString passwordVal = passwordText->GetValue();
  wxString userPass = "Login Button Pressed. \nUsername: " + usernameVal + "\n Password: " + passwordVal;
  wxMessageBox(userPass);
}

login::~login()
{

}

wxBEGIN_EVENT_TABLE (login, wxPanel)
    EVT_BUTTON(loginButton, login::OnLogin)
    EVT_BUTTON(newUserButton, login::OnNewUser)
wxEND_EVENT_TABLE()
