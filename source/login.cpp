#include "login.h"
#include "button.h"
#include "imageInsert.h"

//This panel sets up the panel to log in. It has 2 input boxes and 2 buttons
//It also has the main logo.
login::login(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
  wxFlexGridSizer *verticalBox = new wxFlexGridSizer(3,0,10,10);
  wxBoxSizer *horizontalLogo = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *horizontalBoxTwo = new wxBoxSizer(wxHORIZONTAL);

  Button *login = new Button(wxT("Login"),parent, wxSize(200,100));
  Button *user = new Button(wxT("New User"),parent, wxSize(200,100));

  horizontalBox->Add(login, wxCENTER,0);
  horizontalBox->Add(user, wxCENTER,0);

  horizontalBoxTwo->Add(new wxTextCtrl(this,0,"Login"   ,wxDefaultPosition,
    wxSize(140,60)),1,wxCENTER,0);
  horizontalBoxTwo->Add(new wxTextCtrl(this,0,"Password",wxDefaultPosition,
    wxSize(140,60)),1,wxCENTER,0);

  imageInsert *theLogo = new imageInsert(this, wxT("logo.jpg"), wxBITMAP_TYPE_JPEG,
      wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.2,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.2);

  verticalBox->Add(theLogo, wxCENTER,0);
  verticalBox->Add(horizontalBoxTwo,wxCENTER,0);
  verticalBox->Add(horizontalBox,wxCENTER,0);



  SetSizerAndFit(verticalBox);
  CenterOnParent();
}

login::~login()
{

}
