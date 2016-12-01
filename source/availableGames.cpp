#include "availableGames.h"

availableGames::availableGames(wxWindow *parent, wxSize desiredSize)
    : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, desiredSize,
                 wxLC_REPORT | wxLC_SINGLE_SEL) {
  std::cout << "here" << std::endl;
  this->InsertColumn(0, _("Games"));
  this->InsertColumn(1, _("# of players"));

  long index = this->InsertItem(0, _("Johnye Smith"));
  this->SetItem(index, 1, _("3 of 4"));
}

availableGames::~availableGames() {}
