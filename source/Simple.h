#ifndef SIMPLE_H
#define SIMPLE_H

#include "GameLogic/CrazyEightsGame.hpp"
#include "GameLogic/HeartsGame.hpp"
#include "baseBackground.h"
#include "imageInsert.h"
#include "login.h"
#include "mainMenu.h"
#include "newUser.h"
#include "playArea.h"
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
  CrazyEightsGame *eightsGame;
  HeartsGame *heartsGame;
};

#endif
