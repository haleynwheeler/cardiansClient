#ifndef BASEBACKGROUND_H
#define BASEBACKGROUND_H

#include <wx/wx.h>
#include <wx/sizer.h>

class baseBackground : public wxPanel
{
  wxBitmap backgroundImage;
public:
  baseBackground(wxFrame* parent, wxString file, wxBitmapType format);

  void paintEvent(wxPaintEvent & evt);
  void paintNow();

  void render(wxDC& dc);
  ~baseBackground(){};
  DECLARE_EVENT_TABLE()
};



#endif

/*
Code at https://wiki.wxwidgets.org/An_image_panel aided in the process
of this code.

The image is found at :
https://c2.staticflickr.com/4/3610/3641874356_1b39f97f82_b.jpg
*/
