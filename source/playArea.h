#ifndef playArea_H
#define playArea_H

#include <wx/wx.h>
#include <string>


class playArea: public wxPanel
{

public:
  playArea(wxFrame* parent);
  ~playArea();
  OnButton();
};
#endif
