#ifndef LOGIN_H
#define LOGIN_H

#include <wx/wx.h>


class login: public wxPanel
{
public:
  login(wxFrame* parent);
  void OnNewUser(wxCommandEvent & event);
  void OnLogin(wxCommandEvent & event);
  ~login();

  enum{
    loginButton = 2,
    newUserButton = 3
  };
  wxDECLARE_EVENT_TABLE();
};



#endif
