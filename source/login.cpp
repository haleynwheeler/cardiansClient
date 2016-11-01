#include "login.h"
#include "button.h"
#include "imageInsert.h"

//This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
//It also has the main logo.
login::login(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
  wxBoxSizer *theSizer = new wxBoxSizer(wxHORIZONTAL);

  wxFlexGridSizer *verticalBox = new wxFlexGridSizer(3,1,10,10);
  wxBoxSizer *horizontalLogo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBoxTwo = new wxBoxSizer(wxHORIZONTAL);

  Button *login = new Button(wxT("Login"),parent, wxSize(200,100));
  Button *user = new Button(wxT("New User"),parent, wxSize(200,100));

  horizontalBox->AddStretchSpacer();
  horizontalBox->Add(login, wxCENTER,0);
  horizontalBox->Add(user, wxCENTER,0);
  horizontalBox->AddStretchSpacer();

  horizontalBoxTwo->Add(new wxTextCtrl(this,0,"Login"   ,wxDefaultPosition,
    wxSize(140,60)),1,wxCENTER,0);
  horizontalBoxTwo->Add(new wxTextCtrl(this,0,"Password",wxDefaultPosition,
    wxSize(140,60)),1,wxCENTER,0);

  imageInsert *theLogo = new imageInsert(this, wxT("logo.jpg"), wxBITMAP_TYPE_JPEG,
      200,400);

  verticalBox->Add(theLogo, wxCENTER | wxEXPAND,0);
  verticalBox->Add(horizontalBox,wxALIGN_CENTER_HORIZONTAL,0);
  verticalBox->Add(horizontalBoxTwo,wxCENTER | wxEXPAND,0);
  verticalBox->AddGrowableRow(1, 0);
  theSizer->Add(verticalBox);
  SetSizerAndFit(theSizer);
  Center();
}

login::~login()
{

}
