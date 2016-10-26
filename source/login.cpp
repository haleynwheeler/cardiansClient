#include "login.h"
#include "button.h"
#include "imageInsert.h"

//This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
//It also has the main logo.
login::login(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5,200), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
  wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalLogo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBoxTwo = new wxBoxSizer(wxHORIZONTAL);

  imageInsert *theLogo = new imageInsert(this, wxT("logo.jpg"), wxBITMAP_TYPE_JPEG,
      200,200);
  verticalBox->Add(theLogo);

  Button *login = new Button(wxT("Login"),parent);
  Button *user = new Button(wxT("New User"),parent);

  horizontalBox->Add(login);
  horizontalBox->Add(user);

  horizontalBoxTwo->Add(new wxTextCtrl(this,-1,"Login"   ,wxDefaultPosition,
  wxSize(140,60)),0,wxEXPAND);
  horizontalBoxTwo->Add(new wxTextCtrl(this,-1,"Password",wxDefaultPosition,
  wxSize(140,60)),0,wxEXPAND);
//  verticalBox->Add(horizontalLogo,0,wxCENTER,10);
  verticalBox->AddSpacer(2);
  verticalBox->Add(horizontalBoxTwo,0,wxCENTER,10);
  verticalBox->Add(horizontalBox,0,wxCENTER,10);
  SetSizer(verticalBox);
}

login::~login()
{

}
