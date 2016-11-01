#include "imageInsert.h"
imageInsert::imageInsert(wxPanel* parent, const wxString file,
  wxBitmapType format, int maxHeight, int maxWidth) :wxPanel(parent,wxID_ANY,
    wxDefaultPosition, wxSize(maxHeight,maxWidth), wxTAB_TRAVERSAL, wxPanelNameStr)
{
  wxImage* image = new wxImage(file,format,-1);

  int width = image->GetWidth();
  int height = image->GetHeight();
  double X_Ratio = (double) maxWidth / (double) width;
  double Y_Ratio = (double) maxHeight / (double) height;
  double Ratio = X_Ratio < Y_Ratio ? X_Ratio : Y_Ratio;
  wxImage Image = image->Scale((int)(Ratio*width),(int)(Ratio*height));
  theImage = wxBitmap(Image);
  width = Image.GetWidth();
  height = Image.GetHeight();
  //SetBackgroundColour(wxColour(88,22,79));
  SetSize(height,width);
}

void imageInsert::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  if(theImage.Ok())
  {
    dc.DrawBitmap(theImage,0,0);
  }
}

imageInsert::~imageInsert()
{

}

BEGIN_EVENT_TABLE(imageInsert,wxPanel)
  EVT_PAINT(imageInsert::OnPaint)
END_EVENT_TABLE()
