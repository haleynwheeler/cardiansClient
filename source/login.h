#ifndef LOGIN_H
#define LOGIN_H

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <string>


class login: public wxPanel
{
public:
  login(wxFrame* parent);
  void OnNewUser(wxCommandEvent & event);
  void OnLogin(wxCommandEvent & event);
  wxTextCtrl *usernameText;
  wxTextCtrl *passwordText;
  ~login();

  enum{
    loginButton = 2,
    newUserButton = 3
  };
  wxDECLARE_EVENT_TABLE();
};



#endif
