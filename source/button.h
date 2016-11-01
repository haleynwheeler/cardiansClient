#ifndef BUTTON_H
#define BUTTON_H

#include <wx/wx.h>

class Button: public wxPanel{
//  wxButton theButton;
public:
  //Passing in what's on the button
    Button(const wxString& title, wxFrame* parent, wxSize size);
  //What to do when you click the button
  void OnClick(wxCommandEvent & event);
  DECLARE_EVENT_TABLE()
};
enum
    {
      BUTTON_Hello = wxID_HIGHEST + 1 // declares an id which will be used to call our button
    };


#endif
