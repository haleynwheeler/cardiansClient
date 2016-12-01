#ifndef availableGames_H
#define availableGames_H

#include <wx/listctrl.h>
#include <wx/wx.h>

class availableGames : public wxListCtrl {
  // class availableGames : public wxListCtrl {

public:
  availableGames(wxWindow *parent, wxSize desiredSize);
  ~availableGames();
};
#endif
