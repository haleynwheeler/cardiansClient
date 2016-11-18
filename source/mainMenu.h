#ifndef MAINMENU_H
#define MAINMENU_H

#include <wx/wx.h>
#include <wx/collpane.h>


class mainMenu: public wxPanel{
public:
  mainMenu(wxFrame *parent);
  //void OnPaint(wxPaintEvent & event);
  //void paintingEvent(wxPaintEvent * evt);
  //void render(wxDC& dc);
//  void paintNow();

wxStaticText *heartsLabel;
wxStaticText *eightsLabel;
wxCollapsiblePane *sidePane;

//
enum{
  heartsLocalBtn = 10,
  heartsOnlineBtn = 11,
  eightsLocalBtn = 12,
  eightsOnlineBtn = 13,
  testButton = 14
};

void OnPaint(wxPaintEvent & event){
  wxPaintDC paintDC(this);
  paintDC.SetBrush(wxBrush(wxColour(90,5,18,wxALPHA_OPAQUE)));
  paintDC.SetPen(wxPen(wxColour(90,5,18,wxALPHA_OPAQUE)));
  paintDC.DrawRectangle(0,0,2500,60);
  //paintDC.DrawRectangle(500,0,500,60);
}

 wxDECLARE_EVENT_TABLE();
};

#endif
