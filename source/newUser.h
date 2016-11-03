#ifndef NEWUSER_H
#define NEWUSER_H

#include <wx/wx.h>


class newUser: public wxPanel
{
public:
  newUser(wxFrame* parent);
  void OnNewUser(wxCommandEvent & event);
  wxTextCtrl *usernameText;
  wxTextCtrl *passwordText;
  ~newUser();

  enum{
    newUserButton = 4
  };
  wxDECLARE_EVENT_TABLE();
};



#endif
