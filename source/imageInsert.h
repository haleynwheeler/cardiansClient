#ifndef IMAGEINSERT_H
#define IMAGEINSERT_H

#include <wx/wx.h>
#include <wx/sizer.h>

class imageInsert : public wxPanel
{
public:
  imageInsert(wxPanel* parent, const wxString file, wxBitmapType format, int maxHeight, int maxWidth);
  ~imageInsert();
  void OnPaint(wxPaintEvent& event);
private:
  wxBitmap theImage;
  DECLARE_EVENT_TABLE()
};

#endif
