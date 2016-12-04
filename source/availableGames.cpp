#include "availableGames.h"

availableGames::availableGames(wxWindow *parent, wxSize desiredSize)
    : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, desiredSize,
                 wxLC_REPORT | wxLC_SINGLE_SEL) {
  std::cout << "here" << std::endl;
  numOfGames = 1;
  this->InsertColumn(0, _("Games"), wxLIST_FORMAT_LEFT, 300);
  this->InsertColumn(1, _("# of players"), wxLIST_FORMAT_RIGHT);
  // this->InsertColumn(1, _("# of players")); int format=wxLIST_FORMAT_LEFT,
  // int width=wxLIST_AUTOSIZE
}

void availableGames::appendGames(LobbyGame game) {
  wxString numPlayers = std::to_string(game.numberJoined);
  wxString theGame = game.name + "   " + numPlayers + " of 4";
  wxListItem info;
  info.SetImage(0);
  info.SetId(GetItemCount() + 1);
  info.SetColumn(0);
  info.SetText(game.name);
  InsertItem(GetItemCount(), info.GetText(), 0);
}

wxString availableGames::getSelect() {
  long item = -1;
  item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
  std::cout << GetItemText(item, 0) << std::endl;
  return GetItemText(item, 0);
}

void availableGames::clearAllGames() { DeleteAllItems(); }

availableGames::~availableGames() {}
