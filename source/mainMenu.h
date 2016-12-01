#ifndef MAINMENU_H
#define MAINMENU_H

#include "clientInfo.h"
#include <wx/collpane.h>
#include <wx/wx.h>

class mainMenu : public wxPanel {
public:
  mainMenu(wxFrame *parent);
  // void OnPaint(wxPaintEvent & event);
  // void paintingEvent(wxPaintEvent * evt);
  // void render(wxDC& dc);
  //  void paintNow();

  wxStaticText *heartsLabel;
  wxStaticText *eightsLabel;
  wxCollapsiblePane *sidePane;
  clientInfo *screenInfo = new clientInfo();

  //
  enum {
    heartsLocalBtn = 10,
    heartsOnlineBtn = 11,
    eightsLocalBtn = 12,
    eightsOnlineBtn = 13,
    testButton = 14
  };

  void OnPaint(wxPaintEvent &event) {
    wxPaintDC paintDC(this);
    paintDC.SetBrush(wxBrush(wxColour(90, 5, 18, wxALPHA_OPAQUE)));
    paintDC.SetPen(wxPen(wxColour(90, 5, 18, wxALPHA_OPAQUE)));
    paintDC.DrawRectangle(0, 0, screenInfo->getClientScreenSize().GetWidth(),
                          screenInfo->getClientScreenSize().GetHeight() * .12);
    // paintDC.DrawRectangle(500,0,500,60);
  }

  wxDECLARE_EVENT_TABLE();
};

#endif
