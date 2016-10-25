#include "baseBackground.h"
#include <wx/wx.h>
#include <wx/sizer.h>

baseBackground::baseBackground(wxFrame* parent, wxString file,
  wxBitmapType format): wxPanel(parent)
  {
    backgroundImage.LoadFile(file,format);
  }

void baseBackground::paintEvent(wxPaintEvent & evt)
{
  wxPaintDC dc(this);
  render(dc);
}

void baseBackground::paintNow()
{
  wxPaintDC dc(this);
  render(dc);
}

void baseBackground::render(wxDC& dc)
{
  dc.DrawBitmap( backgroundImage, 0, 0, false );
}

BEGIN_EVENT_TABLE(baseBackground, wxPanel)
 EVT_PAINT(baseBackground::paintEvent)
END_EVENT_TABLE()
