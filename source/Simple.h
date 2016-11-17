#ifndef SIMPLE_H
#define SIMPLE_H

#include "baseBackground.h"
#include "imageInsert.h"
#include "login.h"
#include "mainMenu.h"
#include "newUser.h"
#include <wx/wx.h>

class Simple : public wxFrame {
public:
  Simple(const wxString &title);
  void switchPage(wxString buttonSwitch);
  wxBoxSizer *pageSizer;
  wxBoxSizer *backgroundSizer;

  login *loginPane;
  mainMenu *mainPane;
  wxButton *buttonText;
  newUser *newUserPane;
};

#endif
