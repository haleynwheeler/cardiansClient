#include "login.h"

login::login(wxFrame* parent): wxPanel(parent){
  wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *horizontalBox = new wxBoxSizer(wxHORIZONTAL);

  wxButton *login = new wxButton(this,-1,wxT("Login"));
  wxButton *user = new wxButton(this,-1,wxT("New User"));

  horizontalBox->Add(login);
  horizontalBox->Add(user);

  verticalBox->Add(new wxTextCtrl(this,-1,"Login",wxDefaultPosition,
  wxSize(140,60)),0);
  verticalBox->Add(horizontalBox,0,wxALIGN_RIGHT | wxRIGHT | wxBOTTOM,10);
  SetSizer(verticalBox);

}

login::~login()
{

}
