#ifndef availableGames_H
#define availableGames_H

#include "Messages/LobbyGame.hpp"
#include <wx/listctrl.h>
#include <wx/wx.h>

class availableGames : public wxListCtrl {
  // class availableGames : public wxListCtrl {
  int numOfGames;

public:
  availableGames(wxWindow *parent, wxSize desiredSize);
  ~availableGames();
  void appendGames(LobbyGame game);
  void clearAllGames();
  wxString getSelect();
};
#endif
