#ifndef NEWUSER_H
#define NEWUSER_H

#include <wx/wx.h>


class newUser: public wxPanel
{
public:
  newUser(wxFrame* parent);
  void OnNewUser(wxCommandEvent & event);
  //void OnLogin(wxCommandEvent & event);
  ~newUser();

  enum{
    //loginButton = 2,
    newUserButton = 3
  };
  wxDECLARE_EVENT_TABLE();
};



#endif
