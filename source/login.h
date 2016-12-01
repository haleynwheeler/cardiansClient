#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <wx/textctrl.h>
#include <wx/wx.h>

class login : public wxPanel {
public:
  login(wxFrame *parent);
  void OnNewUser(wxCommandEvent &event);
  void OnLogin(wxCommandEvent &event);
  void receivedLoginFromServer(std::string msg, wxCommandEvent &event);
  wxTextCtrl *usernameText;
  wxTextCtrl *passwordText;
  ~login();

  enum { loginButton = 2, newUserButton = 3 };
  wxDECLARE_EVENT_TABLE();
};

#endif
