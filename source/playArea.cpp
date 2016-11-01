#include "playArea.h"
#include "button.h"
#include "imageInsert.h"

playArea::playArea(wxFrame* parent): wxPanel(parent,wxID_ANY,wxDefaultPosition,
    wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*.5,wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*.5), wxTAB_TRAVERSAL, wxPanelNameStr)
  {


  }


playArea::~playArea(){

}
