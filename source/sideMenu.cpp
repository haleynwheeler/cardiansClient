#include "button.h"

sideMenu:sideMenu(wxFrame* parent): wxCollapsiblePane(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {
