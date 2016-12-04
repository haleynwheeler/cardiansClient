#include "availableGames.h"

availableGames::availableGames(wxWindow *parent, wxSize desiredSize)
    : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, desiredSize,
                 wxLC_REPORT | wxLC_SINGLE_SEL) {
  std::cout << "here" << std::endl;
  numOfGames = 0;
  this->InsertColumn(0, _("Games"));
  // this->InsertColumn(1, _("# of players"));
}

void availableGames::appendGames(LobbyGame game) {
  // wxString newItem = game.name;
  // this->InsertItem();
  // wxString numPlayers = std::to_string(game.joinedPlayers.back());
  // std::cout << game.joinedPlayers.at(0) << std::endl;
  // wxListItem info;
  // info.SetImage(0);
  // info.SetId(GetItemCount() + 1);
  // info.SetText(newItem);
  // info.SetColumn(0);
  // SetItem(info.GetId(), info, -1);
  InsertItem(GetItemCount(), game.name, 0);
  // InsertItem(GetItemCount(), numPlayers, 0);
  std::cout << GetItemCount() << std::endl;
}

void availableGames::clearAllGames() { DeleteAllItems(); }

availableGames::~availableGames() {}
