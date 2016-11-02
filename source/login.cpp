#include "login.h"
#include "button.h"
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


  verticalOne->Add(new wxTextCtrl(this,0,"Login",wxDefaultPosition,
    wxSize(140,60)),1,wxCENTER,0);
   wxButton *login = new wxButton(this, wxID_ANY, wxT("Login"), wxDefaultPosition,
   wxSize(200,100), 0, wxDefaultValidator, wxButtonNameStr);
    // Button *login = new Button(wxT("Login"),parent, wxSize(400,100));
  verticalOne->Add(login);

  login->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
  login->SetForegroundColour(wxColour(wxT("WHITE")));

  // Button *user = new Button(wxT("New User"),parent, wxSize(100,100));
  verticalTwo->Add(new wxTextCtrl(this,0,"Password",wxDefaultPosition,
  wxSize(140,60)),1,wxCENTER,0);
  wxButton *user = new wxButton(this, wxID_ANY, wxT("User"), wxDefaultPosition,
      wxSize(200,100), 0, wxDefaultValidator, wxButtonNameStr);
   verticalTwo->Add(user);

   user->SetBackgroundColour(wxColour(90,5,18,wxALPHA_OPAQUE));
   user->SetForegroundColour(wxColour(wxT("WHITE")));

  horizontalContainer->Add(verticalOne);
  horizontalContainer->Add(verticalTwo);

  theSizer->Add(theLogo);
  theSizer->Add(horizontalContainer);

  SetSizerAndFit(theSizer);
  Center();
}

login::~login()
{

}
